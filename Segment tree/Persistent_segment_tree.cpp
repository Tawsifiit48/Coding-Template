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

#define SZ 120003

vi v[SZ];

int st[20*SZ], L[20*SZ], R[20*SZ], nxt, nn, val[SZ], root[SZ];

void build(int node, int b, int e) {
    if(b == e) return;
    int mid = (b + e) / 2;
    L[node] = ++nxt;
    R[node] = ++nxt;
    build(L[node], b, mid);
    build(R[node], mid + 1, e);
}

int update(int node, int b, int e, int pos) {
    if(b > pos or e < pos) return node;
    int ind = ++nxt;
    if(b >= pos and e <= pos) {
        st[ind] = st[node] + 1;
        return ind;
    }
    int mid = (b + e) / 2;
    L[ind] = update(L[node], b, mid, pos);
    R[ind]  = update(R[node], mid + 1, e, pos);
    st[ind] = st[L[ind]] + st[R[ind]];
    return ind;
}

int query(int node1, int node2, int node3, int node4, int b, int e, int k) {
    if(b == e) return b;
    int crtsum = st[L[node1]] + st[L[node2]] - st[L[node3]] - st[L[node4]];
    int mid = (b + e) / 2;
    if(k > crtsum) return query(R[node1], R[node2], R[node3], R[node4], mid + 1, e, k - crtsum);
    return query(L[node1], L[node2], L[node3], L[node4], b, mid, k);
}

int timer, l, lvl[SZ];
vector<int> tin, tout;
vector<vector<int>> up;
struct LCA {
    void dfs(int u, int p)
    {
        tin[u] = ++timer;
        up[u][0] = p;
        root[u] = update(root[p], 1, nn, val[u]);
        lvl[u] = lvl[p] + 1;
        for (int i = 1; i <= l; ++i)
            up[u][i] = up[up[u][i-1]][i-1];
     
        for (int x : v[u]) {
            if (x != p)
                dfs(x, u);
        }
     
        tout[u] = ++timer;
    }
     
    bool is_ancestor(int x, int y)
    {
        return tin[x] <= tin[y] && tout[x] >= tout[y];
    }
     
    int lca_find(int x, int y)
    {
        if (is_ancestor(x, y))
            return x;
        if (is_ancestor(y, x))
            return y;
        for (int i = 0; i <= l; ++i) {
            if (!is_ancestor(up[x][i], y))
                x = up[x][i];
        }
        return up[x][0];
    }

    int func(int x, int y) {
        if(lvl[x] > lvl[y]) {
            swap(x, y);
        }
        int dis = lvl[y] - lvl[x];
        for(int i = l; i >= 0; i--) {
            if((1 << i)&dis) {
                dis -= (1 << i);
                y = up[y][i];
            }
        }
        if(x == y) {
            return x;
        }
        for(int i = l; i >= 0; i--) {
            if(up[x][i] == up[y][i] or up[x][i] == 0) continue;
            x = up[x][i];
            y = up[y][i];
        }
        return up[x][0];
    }

    void preprocess(int root, int n) {
        tin.resize(n+10);
        tout.resize(n+10);
        timer = 0;
        l = ceil(log2(n));
        up.assign(n + 10, vector<int>(l + 1));
        dfs(root, 0);
    }
};


void solve() {
    int n, q; cin >> n >> q;
    pll arr[n + 10];
    fe(i, 1, n) {
        cin >> arr[i].xx;
        arr[i].yy = i;
    }
    nn = n;
    sort(arr + 1, arr + n + 1);

    fe(i, 2, n) {
        int x, y; cin >> x >> y;
        v[x].pb(y);
        v[y].pb(x);
    }
    fe(i, 1, n) {
        val[arr[i].yy] = i;
    }
    root[0] = 1;
    build(root[0], 1, n);
    LCA sp;
    sp.preprocess(1, n);
    fe(i, 1, q) {
        int x, y, k; cin >> x >> y >> k;
        int l = sp.func(x, y);
        int ind = query(root[x], root[y], root[l], root[up[l][0]], 1, n, k);
        cout << arr[ind].xx << N;
    }
}
// https://www.spoj.com/problems/COT/en/
int main() {
    // FILE;
    fast;
    // int t; cin >> t; while(t--)
    solve();
}
