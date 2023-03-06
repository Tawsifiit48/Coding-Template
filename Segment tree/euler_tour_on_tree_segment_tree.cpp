#include<bits/stdc++.h>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>


using namespace std;
using namespace __gnu_pbds;

#define ll unsigned long long int

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

#define SZ 700
vi v[SZ];
int tme, st[SZ], en[SZ], disc[SZ], vis[SZ], val[SZ], seg[4 * SZ];

void build(int node, int b, int e) {
    if(b == e) {
        seg[node] += val[b];
        return;
    }
    int lt = node << 1;
    int rt = lt + 1;
    int mid = (b + e) / 2;
    build(lt, b, mid);
    build(rt, mid + 1, e);
    seg[node] = seg[lt] + seg[rt];
}

void update(int node, int b, int e, int i) {
    if(b >= i and e <= i) {
        seg[node] = val[b];
        return;
    }
    if(b > i or e < i) return;
    int lt = node << 1;
    int rt = lt + 1;
    int mid = (b + e) / 2;
    update(lt, b, mid, i);
    update(rt, mid + 1, e, i);
    seg[node] = seg[rt] + seg[lt];
}

int query(int node, int b, int e, int i, int j) {
    if(b > j or e < i) return 0;
    if(b >= i and e <= j) return seg[node];
    int lt = node << 1;
    int rt = lt + 1;
    int mid = (b + e) / 2;
    return query(lt, b, mid, i, j) + query(rt, mid + 1, e, i, j);
}

int sp[SZ][20], lvl[SZ];
 
int timer, l;
vector<int> tin, tout;
vector<vector<int>> up;
 
void dfs(int u, int p)
{
    st[u] = ++timer;
    up[u][0] = p;
    lvl[u] = lvl[p] + 1;
    disc[timer] = u;
    for (int i = 1; i <= l; ++i)
        up[u][i] = up[up[u][i-1]][i-1];
 
    for (int x : v[u]) {
        if (x != p)
            dfs(x, u);
    }
 
    en[u] = ++timer;
}
 
bool is_ancestor(int u, int v)
{
    return st[u] <= st[v] && en[u] >= en[v];
}
 
int lca_find(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}
 
void preprocess(int root, int n) {
    tin.resize(n+10);
    tout.resize(n+10);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n + 10, vector<int>(l + 1));
    dfs(root, root);
}

void solve() {
    int n, x, y;
    int arr[n + 10];
    preprocess(1, n);
    fe(i, 1, n) {
        val[st[i]] = arr[i];
        val[en[i]] = -arr[i];
    }
    build(1, 1, timer);
    update(1, 1, timer, st[x]);
    update(1, 1, timer, en[x]);
    int lca = lca_find(x, y);
    if(lca == y) swap(x, y);
    if(lca == x) {
        lca = x;
        int temp = query(1, 1, timer, st[x], st[y]);
    } else {
        int temp = query(1, 1, timer, st[lca], st[x]);
        temp += query(1, 1, timer, st[lca], st[y]);
        temp -= query(1, 1, timer, st[lca], st[lca]);
    }
}
int main() {
    // FILE;
    fast;
    // int t; cin >> t; while(t--)
    solve();
}
