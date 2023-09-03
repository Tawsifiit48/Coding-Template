struct FlowEdge
{
    ll from, to, capacity, cost;
    FlowEdge(ll from, ll to, ll capacity, ll cost) : from(from), to(to), capacity(capacity), cost(cost) {}
};

struct MCMF {

    vector<vector<int>> adj;
    vector<vector< ll>> cost, capacity;
    vector<ll> d, p;
    const ll INF = 1e18;

    int n;

    MCMF(int _n) {
        n = _n + 10;
        adj.assign(n, vector<int>());
        cost.assign(n, vector<ll>(n, 0));
        capacity.assign(n, vector<ll>(n, 0));
        d.resize(n);
        p.resize(n);
    }

    void add_edge(int u, int v, ll cap, ll val) {
        adj[u].pb(v);
        adj[v].pb(u);
        cost[u][v] = val;
        cost[v][u] = -val;
        capacity[u][v] = cap;
    }

    void shortest_paths(int s) {
        d.assign(n, INF);
        d[s] = 0;
        vector<bool> inq(n + 10, false);
        queue<int> q;
        q.push(s);
        p.assign(n, -1);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (int v : adj[u]) {
                if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                    d[v] = d[u] + cost[u][v];
                    p[v] = u;
                    if (!inq[v]) {
                        inq[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }

    ll min_cost_flow(int s, int t, int k) {
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
                f = min(f, capacity[p[cur]][cur]);
                cur = p[cur];
            }

            // apply flow
            flow += f;
            cost += f * d[t];
            cur = t;
            while (cur != s) {
                capacity[p[cur]][cur] -= f;
                capacity[cur][p[cur]] += f;
                cur = p[cur];
            }
        }

        if (flow < k)
            return -1;
        else
            return cost;
    }
};
