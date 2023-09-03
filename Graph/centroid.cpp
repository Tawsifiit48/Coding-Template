vi v[SZ];
 
int sub_tree[SZ], centroid[SZ], par[SZ], lvl[SZ], ans[SZ];
ll sum, crt;  
 
inline int dfs(int u, int p) {
    sub_tree[u] = 1;
    for(auto x : v[u]) {
        if(x != p and centroid[x] == 0) {
            sub_tree[u] += dfs(x, u);
        }
    }
    return sub_tree[u];
}
 
 
int get_centroid(int u, int p, int n) {
    for(auto x : v[u]) {
        if(x != p and centroid[x] == 0 and sub_tree[x] * 2 > n) {
            return get_centroid(x, u, n);
        }
    }
    return u;
}

 
void decompose(int u, int p, int d, int id = 0) {
    dfs(u, -1);
    int c = get_centroid(u, -1, sub_tree[u]);
 
    crt = 0;
    centroid[c] = 1, lvl[c] = d, par[c] = p;
    ans[c] = id;
    for(auto x : v[c]) {
        if(centroid[x] == 0) {
            decompose(x, c, d + 1, id + 1);
        }
    }
}
