struct LCA {
 
    int timer, l, lvl[SZ];
    vector<int> tin, tout;
    vector<vector<int>> up, sp_mn, sp_mx;
    vi t_sort;
     
    void dfs(int u, int p, int c)
    {
        t_sort.pb(u);
        tin[u] = ++timer;
        up[u][0] = p;
        if(u == 1) {
            sp_mn[u][0] = 1e9;
            sp_mx[u][0] = 0;
        } else {
            sp_mn[u][0] = c;
            sp_mx[u][0] = c;
        }
        lvl[u] = lvl[p] + 1;
        for (int i = 1; i <= l; ++i) {
            up[u][i] = up[up[u][i-1]][i-1];
            sp_mn[u][i] = min(sp_mn[u][i - 1], sp_mn[up[u][i-1]][i - 1]);
            sp_mx[u][i] = max(sp_mx[u][i - 1], sp_mx[up[u][i-1]][i - 1]);
        }
     
        for (auto [x, y] : v[u]) {
            if (x != p) {
                dfs(x, u, y);
            }
        }
        tout[u] = ++timer;
    }
     
    bool is_ancestor(int u, int v)
    {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }
     
    int lca_find(int u, int v)
    {
        if (is_ancestor(u, v))
            return u;
        if (is_ancestor(v, u))
            return v;
        for (int i = l; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v))
                u = up[u][i];
        }
        return up[u][0];
    }
     
    int lift_dis(int a, int dist)
    {
        for(int i = l; i >= 0; i--)
        {
            if((1 << i) <= dist) {
                a = up[a][i], dist -= (1 << i);
            }
        }
        return a;
    }

    void preprocess(int root, int n) {
        tin.resize(n+10);
        tout.resize(n+10);
        timer = 0;
        l = ceil(log2(n));
        up.assign(n + 10, vector<int>(l + 1));
        sp_mn.assign(n + 10, vector<int>(l + 1));
        sp_mx.assign(n + 10, vector<int>(l + 1));
        
        dfs(root, 1, 0);
    }

    pii func(int x, int y) {
        if(lvl[x] > lvl[y]) {
            swap(x, y);
        }
        int dis = lvl[y] - lvl[x];
        int ans1 = sp_mx[y][0];
        int ans2 = sp_mn[y][0];
        for(int i = l; i >= 0; i--) {
            if((1 << i)&dis) {
                dis -= (1 << i);
                ans1 = max(ans1, sp_mx[y][i]);
                ans2 = min(ans2, sp_mn[y][i]);
                y = up[y][i];
            }
        }
        if(x == y) {
            return {ans1, ans2};
        }
        for(int i = l; i >= 0; i--) {
            if(up[x][i] == up[y][i] or up[x][i] == 0) continue;
            ans1 = max(ans1, sp_mx[x][i]);
            ans1 = max(ans1, sp_mx[y][i]);
            ans2 = min(ans2, sp_mn[x][i]);
            ans2 = min(ans2, sp_mn[y][i]);
            x = up[x][i];
            y = up[y][i];
        }
        ans1 = max(ans1, sp_mx[x][0]);
        ans1 = max(ans1, sp_mx[y][0]);
        ans2 = min(ans2, sp_mn[x][0]);
        ans2 = min(ans2, sp_mn[y][0]);
        return {ans1, ans2};
    }
};
