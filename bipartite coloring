int col[SZ], vis[SZ];
bool color(ll u, ll c) {
    col[u] = c;
    vis[u] = 1;
    
    bool pos = 1;
    for (ll x: v[u]) {
        if (!vis[x]) {
            pos &= color(x, !c);
        } else {
            if (c == col[x]) return 0;
        }
    }
    return pos;
}
