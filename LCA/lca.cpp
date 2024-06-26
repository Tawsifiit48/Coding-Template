
struct LCA {
 
    int timer, l, lvl[SZ];
    vector<int> tin, tout;
    vector<vector<int>> up;
     
    void dfs(int u, int p)
    {
        tin[u] = ++timer;
        up[u][0] = p;
        lvl[u] = lvl[p] + 1;
        for (int i = 1; i <= l; ++i)
            up[u][i] = up[up[u][i-1]][i-1];
     
        for (int x : v[u]) {
            if (x != p)
                dfs(x, u);
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
 
    int func(int x, int y) {
        if(lvl[x] > lvl[y]) {
            swap(x, y);
        }
        int dis = lvl[y] - lvl[x];
        for(int i = l; i >= 0; i--) {
            if((1 << i)&dis) {
                dis -= (1 << i);
                y = up[y][i];
            }
        }
        if(x == y) {
            return x;
        }
        for(int i = l; i >= 0; i--) {
            if(up[x][i] == up[y][i] or up[x][i] == 0) continue;
            x = up[x][i];
            y = up[y][i];
        }
        return up[x][0];
    }
     
    int lift_dis(int a, int dist)
    {
        for(int i = 18; i >= 0; i--)
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
        dfs(root, 0);
    }
};
