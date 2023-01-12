int vis[SZ], tin[SZ], lw[SZ], tme;

void dfs(int u, int p) {
    vis[u] = 1;
    lw[u] = tin[u] = ++tme;
    for(auto x : v[u]) {
        if(p == x) continue;
        if(vis[x]) {
            lw[u] = min(lw[u], tin[x]); 
        } else {
            dfs(x, u);
            lw[u] = min(lw[u], lw[x]);
            if(lw[x] > tin[u]) {
                //bridge
            }
        }
    }    
}
