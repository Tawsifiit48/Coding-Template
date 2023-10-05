struct Edge {
    ll v, rpos;
    ll cap, cost, flow = 0;
    Edge() {}
    Edge(ll v, ll p, ll cap, ll c) : v(v), rpos(p), cap(cap), cost(c) {}
    
};

struct mcmf {
    ll INF = 1e18;
    ll n;
    vector < vector < Edge >> E;
    ll mCap[SZ], dis[SZ];
    ll par[SZ], pos[SZ];
    bitset < SZ > vis;
    mcmf(ll n) : n(n), E(n) {}

    void add_edge(ll u, ll v, ll cap, ll cost = 0) {
        E[u].emplace_back(v, E[v].size(), cap, cost);
        E[v].emplace_back(u, E[u].size() - 1, 0, -cost);
    }

    inline bool spfa(ll s, ll t) {
        vis.reset();
        for(ll i = 0; i < n; i++) {
            mCap[i] = dis[i] = INF;
        }
        queue < ll > q;
        q.push(s);
        dis[s] = 0, vis[s] = 1;
        
        while(!q.empty()) {
            ll i = 0;
            ll u = q.front(); q.pop();
            vis[u] = 0;
            for(auto &e : E[u]) {
                ll v = e.v;
                ll f = e.cap - e.flow, w = dis[u] + e.cost;
                if(f > 0 and dis[v] > w) {
                    dis[v] = w;
                    par[v] = u;
                    pos[v] = i;
                    mCap[v] = min(mCap[u], f);
                    if(!vis[v]) q.push(v);
                    vis[v] = 1;
                }
                i++;
            }
        }
        return dis[t] != INF;
    }

    ll min_cost_flow(ll s, ll t, ll &need) {
        ll C = 0;
        while(need and spfa(s, t)) {
            ll v = t;
            ll f = min(mCap[v], need);
            need -= f;
            while(v != s) {
                ll u = par[v];
                Edge &e = E[u][pos[v]];
                e.flow += f;
                E[v][e.rpos].flow -= f;
                v = u;
            }
            C += dis[t] * f; 
        }
        return C;
    }
};
