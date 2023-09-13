struct edge {
    int u, v;
    long long capacity, flow = 0;
    edge(int u, int v, long long capacity) : u(u), v(v), capacity(capacity) {}
};
 
struct Dinic {
    int s, t, id = 0, n;
    const long long INF = 0x3f3f3f3f3f3f3f3f;
    vector <edge> edges;
    vector <vector <int> > adj;
    vector <int> lvl, ptr;
    queue  <int> Q;
 
    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        lvl.resize(n);
        ptr.resize(n);
    }
 
    void add_edge(int u, int v, long long capacity) {
        edges.push_back(edge(u, v, capacity));
        edges.push_back(edge(v, u, 0));
        adj[u].push_back(id);
        adj[v].push_back(id + 1);
        id += 2;
    }
 
    int bfs() {
        fill(lvl.begin(), lvl.end(), -1);
        fill(ptr.begin(), ptr.end(),  0);
        Q.push(s);
        lvl[s] = 0;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(int i = 0; i < adj[u].size(); i++) {
                if(lvl[edges[adj[u][i]].v] != -1 || edges[adj[u][i]].capacity - edges[adj[u][i]].flow == 0)
                        continue;
                lvl[edges[adj[u][i]].v] = lvl[u] + 1;
                Q.push(edges[adj[u][i]].v);
            }
        }
        return lvl[t] != -1;
    }
 
    int dfs(int u, long long pushed) {
       if(!pushed || u == t)
            return pushed;
       for(int& i = ptr[u]; i < adj[u].size(); i++) {
            int idx = adj[u][i];
            int v = edges[idx].v;
            if(lvl[v] != lvl[u] + 1)
                continue;
            long long x = dfs(v, min(pushed, edges[idx].capacity - edges[idx].flow));
            if(x > 0) {
                edges[idx ^ 0].flow += x;
                edges[idx ^ 1].flow -= x;
                return x;
            }
       }
       return 0;
    }
 
    long long maxFlow() {
        long long flow = 0, x;
        while(bfs())
           while(x = dfs(s, INF)) {
                flow += x;
           }
        return flow;
    }
};
