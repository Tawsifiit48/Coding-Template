int lead[SZ], chain[SZ], lvl[SZ], pos[SZ], sub[SZ], par[SZ];
int chain_no, timer;

struct HLD {

    void init(int n) {
        fe(i, 1, n) {
            lead[i] = chain[i] = lvl[i] = pos[i] = sub[i] = par[i] = 0;
        }
        chain_no = timer = 0;
    }

    void dfs(int u, int p, int l = 0) {
        sub[u] = 1;
        lvl[u] = l;
        par[u] = p;
        for(auto x : v[u]) {
            if(x == p) continue;
            dfs(x, u, l + 1);
            sub[u] += sub[x];
        }
    }

    void hld(int u, int crt, int flag) {
        if(flag) {
            crt = ++chain_no;
            lead[crt] = u;
        }
        chain[u] = crt;
        pos[u] = ++timer;
        ll mx = -1;
        for(auto x : v[u]) {
            if(x == par[u]) continue;
            if(mx == -1) mx = x;
            else if(sub[x] > sub[mx]) mx = x;
        }
        if(mx == -1) return;
        
        hld(mx, crt, 0);

        for(auto x : v[u]) {
            if(x == par[u] or mx == x) continue;
            hld(x, 0, 1);
        }
    }

    void hld_update(int x, int y, ll val) {
        while(chain[x] != chain[y]) {
            if(lvl[lead[chain[x]]] < lvl[lead[chain[y]]]) {
                //update (pos[lead[chain[y]]], pos[y])
                y = par[lead[chain[y]]];
            } else {
                //update (pos[lead[chain[x]]], pos[x])
                x = par[lead[chain[x]]];
            }
        }
        if(lvl[x] < lvl[y]) {
            //update (pos[x] + 1, pos[y])   
        } else {
            //update(pos[y] + 1, pos[x]);
        }
    }

    ll hld_query(int x, int y) {
        ll ret = 1e15;
        while(chain[x] != chain[y]) {
            if(lvl[lead[chain[x]]] < lvl[lead[chain[y]]]) {
                //ret = cmp(ret, query(pos[lead[chain[y]]], pos[y]))
                y = par[lead[chain[y]]];
            } else {
                //ret = cmp(ret, query(pos[lead[chain[x]]], pos[x]))
                x = par[lead[chain[x]]];
            }
        }
        if(lvl[x] < lvl[y]) {
            //ret = cmp(ret, query(pos[x] + 1, pos[y]));   
        } else {
            //ret = cmp(ret, query(pos[y] + 1, pos[x]));   
        }
        return ret;
    }
};
