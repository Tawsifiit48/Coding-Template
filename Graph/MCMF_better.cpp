struct FlowEdge
{
    ll from, to, capacity, cost, backedge;
    FlowEdge(ll from, ll to, ll capacity, ll cost, ll backedge) : from(from), to(to), capacity(capacity), cost(cost), backedge(backedge) {}
};
vector<vector<FlowEdge>> adj;
vector<ll> d, p, from_edge;

struct MCMF {

    const ll INF = 1e18;

    int n;

    MCMF(int _n) {
        n = _n + 10;
        adj.assign(n, vector<FlowEdge>());
        d.resize(n);
        p.resize(n);
    }

    void add_edge(int u, int v, ll cap, ll val) {
        adj[u].pb(FlowEdge(u, v, cap, val, adj[v].size()));
        adj[v].pb(FlowEdge(v, u, 0, -val, adj[u].size() - 1));
    }

    void shortest_paths(int s) {
        d.assign(n, INF);
        from_edge.assign(n, -1);
        d[s] = 0;
        vector<int> inq(n + 10, 0);
        queue<int> q;
        q.push(s);
        p.assign(n, -1);
        inq[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for (int i = 0; i < adj[u].size(); i++) {
                FlowEdge a = adj[u][i];
                if (a.capacity > 0 && d[a.to] > d[u] + a.cost) {
                    d[a.to] = d[u] + a.cost;
                    p[a.to] = u;
                    from_edge[a.to] = i;
                    if (inq[a.to] != 1) {
                        inq[a.to] = 1;
                        q.push(a.to);
                    }
                }
            }
        }
    }

    ll min_cost_flow(int s, int t, ll k) {
        ll flow = 0;
        ll cost = 0;
        while (flow < k) {
            shortest_paths(s);
            if (d[t] == INF)
                break;

            // find max flow on that path
            ll f = k - flow;
            int cur = t;
            while (cur != s) {
                f = min(f, adj[p[cur]][from_edge[cur]].capacity);
                cur = p[cur];
            }

            // apply flow
            flow += f;
            cost += f * d[t];
            cur = t;
            while (cur != s) {
                adj[p[cur]][from_edge[cur]].capacity -= f;
                adj[cur][adj[p[cur]][from_edge[cur]].backedge].capacity += f;
                cur = p[cur];
            }
        }
        if (flow < k)
            return -1;
        else
            return cost;
    }
};
