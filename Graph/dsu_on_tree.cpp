ll sub[SZ], bg[SZ], ans[SZ];

void dfs(int u, int p) { //dfs(1, -1)
    sub[u] = 1;
    lvl[u] = lvl[p] + 1;
    for(auto x : v[u]) {
        if(x == p) continue;
        dfs(x, u);
        sub[u] += sub[x];
    }
}


void add(int u, int p, int inc) { 
    // manupulate function
    for(auto x : v[u]) {
        if(x == p or bg[x]) continue;
        add(x, u, inc);
    }
}


void dfs(int u, int p, int keep) { //dfs(1, -1, 0)
    int mx = -1, bigchild = -1;
    for(auto x : v[u]) {
        if(x == p) continue;
        if(sub[x] > mx) {
            bigchild = x;
            mx = sub[x];
        }
    }

    for(auto x : v[u]) {
        if(x == p or x == bigchild) continue;
        dfs(x, u, 0);
    }
    if(bigchild != -1) {
        dfs(bigchild, u, 1);
        bg[bigchild] = 1;
    }
    add(u, p, 1);
    // store answer in node u by any process


    if(bigchild != -1) {
        bg[bigchild] = 0;
    }
    if(keep == 0) {
        add(u, p, -1);
    }
}
