vi adj[SZ], rev[SZ];
vi order;
int vis[SZ];

void dfs(int u) { // u->v, u comes later then v 
    vis[u] = 1; // so reverse dfs can get max
    for(auto x : adj[u]) { // connected component
        if(vis[x]) continue; // in a directed graph
        dfs(x);
    }
    order.pb(u);
}


void dfs1(int u) { // do dfs1 from reverse ordering
    vis[u] = 1;
    for(auto x : adj[u]) {
        if(vis[x]) continue;
        dfs1(x);
    }
}
