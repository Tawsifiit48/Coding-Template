#include<bits/stdc++.h>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>


using namespace std;
using namespace __gnu_pbds;
 
#define ll long long int
 
#define pb push_back
#define mp make_pair
#define xx first
#define yy second
 
#define pii pair <int, int >
#define pll pair < ll, ll >
#define xx first
#define yy second
#define vi vector < int >
#define vl vector < ll >
#define vp vector < pii >
 
  
#define fe(i, c, n) for(int i = c; i <= n; i++)
#define fr(i, n, c) for(int i = n; i >= c; i--)
 
#define be(a) a.begin(), a.end()
#define mem(a) memset(a, 0, sizeof(a))
#define memn(a) memset(a, -1, sizeof(a))
#define S " "
#define N "\n"
 
bool checkBit(ll n, ll i){ return (n&(1LL<<i)); }
ll setBit(ll n, ll i){ return (n|(1LL<<i)); }
ll resetBit(ll n, ll i){ return (n&(~(1LL<<i))); }
 
#define fast ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0)

template<typename temp>using ordered_set = tree<temp, null_type, less_equal<temp>, rb_tree_tag,tree_order_statistics_node_update>;
//order_of_key(k)  : Number of items strictly smaller than k .
//find_by_order(k) : K-th element in a set (counting from zero).//*(ost.find_by_order(k))

const ll MX = 1e18;
const ll mod = 1e9 + 7;

#define SZ 200003


ll lazy[4 * SZ], st[4 * SZ];

int n, m;

inline void push(int node, int b, int e) {
    if (lazy[node] == 1e15) return;
    st[node] = min(lazy[node], st[node]);
    if (b != e) {
        int l = node << 1;
        int r = l + 1;
        lazy[l] = min(lazy[l], lazy[node]);
        lazy[r] = min(lazy[r], lazy[node]);
    }
    lazy[node] = 1e15;
}

inline long long combine(long long a,long long b) {
    return min(a, b);
}

inline void pull(int node) {
    st[node] = min(st[node << 1], st[(node << 1) | 1]);
}

void build(int node, int b, int e) {
    lazy[node] = st[node] = 1e15;
    if (b == e) {
        return;
    }
    int mid = (b + e) >> 1;
    int l = node << 1;
    int r = l + 1;
    build(l, b, mid);
    build(r, mid + 1, e);
    pull(node);
}
void upd(int node, int b, int e, int i, int j, ll val) {
    push(node, b, e);
    if(j < b || e < i) return;
    if(i <= b && e <= j) {
        lazy[node] = min(lazy[node], val); //set lazy
        push(node, b, e);
        return;
    }
    int mid = (b + e) >> 1;
    int l = node << 1;
    int r = l + 1;
    upd(l, b, mid, i, j, val);
    upd(r, mid + 1, e, i, j, val);
    pull(node);
}

ll query(int node, int b, int e, int i, int j) {
    push(node, b, e);
    if (i > e || b > j) return 1e15;
    if (i <= b && e <= j) return st[node];
    int mid = (b + e) >> 1;
    int l = node << 1;
    int r = l + 1;
    return combine(query(l, b, mid, i, j), query(r, mid + 1, e, i, j));
}


vi v[SZ];

ll lead[SZ], chain[SZ], lvl[SZ], pos[SZ], sub[SZ], par[SZ];
ll chain_no, timer;

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
                upd(1, 1, n, pos[lead[chain[y]]], pos[y], val);
                y = par[lead[chain[y]]];
            } else {
                //update (pos[lead[chain[x]]], pos[x])
                upd(1, 1, n, pos[lead[chain[x]]], pos[x], val);
                x = par[lead[chain[x]]];
            }
        }
        if(lvl[x] < lvl[y]) {
            //update (pos[x] + 1, pos[y])  
            upd(1, 1, n, pos[x] + 1, pos[y], val); 
        } else {
            //update(pos[y] + 1, pos[x]);
            upd(1, 1, n, pos[y] + 1, pos[x], val); 
        }
    }

    ll hld_query(int x, int y) {
        ll ret = 1e15;
        while(chain[x] != chain[y]) {
            if(lvl[lead[chain[x]]] < lvl[lead[chain[y]]]) {
                //ret = cmp(ret, query(pos[lead[chain[y]]], pos[y]))
                ret = min(ret, query(1, 1, n, pos[lead[chain[y]]], pos[y]));
                y = par[lead[chain[y]]];
            } else {
                //ret = cmp(ret, query(pos[lead[chain[x]]], pos[x]))
                ret = min(ret, query(1, 1, n, pos[lead[chain[x]]], pos[x]));
                x = par[lead[chain[x]]];
            }
        }
        if(lvl[x] < lvl[y]) {
            //ret = cmp(ret, query(pos[x] + 1, pos[y]));   
            ret = min(ret, query(1, 1, n, pos[x] + 1, pos[y]));
        } else {
            //ret = cmp(ret, query(pos[y] + 1, pos[x]));   
            ret = min(ret, query(1, 1, n, pos[y] + 1, pos[x]));
        }
        return ret;
    }
    //dfs(1, 1);
    //hld(1, 0, 1);
};

int parent[SZ], child[SZ];

void make_set(int a) {
    parent[a] = a;
    child[a] = 1;
}

int find_set(int a) {
    if (a == parent[a])
        return a;
    return parent[a] = find_set(parent[a]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (child[a] < child[b])
            swap(a, b);
        parent[b] = a;
        child[a] += child[b];
    }
}

struct Edge {
    int u, v;
    ll weight;
    int id;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

void pre(int n) {
    fe(i, 1, n) {
        make_set(i);
    }
}

int ismst[SZ];
ll ans[SZ];

void solve() {
    cin >> n >> m;
    pre(n);
    vector < Edge > e;
    fe(i, 1, m) {
        int x, y; ll z; cin >> x >> y >> z;
        e.pb({x, y, z, i});
    }
    sort(be(e));
    ll sum = 0;
    for(auto [x, y, z, a] : e) {
        if(find_set(x) != find_set(y)) {
            union_sets(x, y);
            sum += z;
            v[x].pb(y);
            v[y].pb(x);
            ismst[a] = 1;
        }
    }

    HLD sp;
    sp.init(n);
    sp.dfs(1, 1);
    sp.hld(1, 0, 1);

    build(1, 1, n);
    for(auto [x, y, z, a] : e) {
        if(!ismst[a]) {
            sp.hld_update(x, y, z);
        }
    }
    for(auto [x, y, z, a] : e) {
        if(!ismst[a]) {
            ans[a] = sum;
        } else {
            ll crt = sum - z;
            ll temp = sp.hld_query(x, y);
            if(temp == 1e15) {
                crt = -1;
            } else crt += temp;
            ans[a] = crt;
        }
    }

    fe(i, 1, m) {
        cout << ans[i] << endl;
    }

    fe(i, 1, m) {
        ismst[i] = ans[i] = 0;
    }

    fe(i, 1, n) {
        v[i].clear();
    }
}
//https://www.codechef.com/problems/KOL1507?tab=statement
int main() {
    // FILE;
    fast;
    int t; cin >> t; while(t--)
    solve();
}
