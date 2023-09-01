struct bpm{
    const int inf = 0x3f3f3f3f;
    vector <vector <int> > G;
    vector <int> match, dist;
    int n, m;
    bpm(int n, int m) : n(n), m(m) {
        G.resize(n + 1);
        match.resize(n + m + 1, 0);
        dist.resize(n + 1);
    }
    void add_edge(int i, int j) {
        G[i].push_back(j);
    }
    bool bfs() {
        queue <int> Q;
        fill(dist.begin(), dist.end(), inf);
        for(int i = 1; i <= n; i++) if(!match[i]) {
            dist[i] = 0;
            Q.push(i);
        }
        while(Q.size()) {
            int u = Q.front(); Q.pop();
            if(!u) continue;
            for(int v: G[u]) if(dist[match[v]] == inf) {
                dist[match[v]] = 1 + dist[u];
                Q.push(match[v]);
            }
        }
        return dist[0] != inf;
    }
    bool dfs(int u) {
        if(!u) return true;
        for(int x: G[u]) {
            int v = match[x];
            if(dist[v] == dist[u] + 1 && dfs(v)) {
                match[u] = x;
                match[x] = u;
                return true;
            }
        }
        dist[u] = inf;
        return false;
    }
    int get() {
        int ans = 0;
        while(bfs()) {
            for(int i = 1; i <= n; i++) if(!match[i] && dfs(i)) ++ans;
        }
        return ans;
    }
};
