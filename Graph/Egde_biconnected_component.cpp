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

#ifndef ONLINE_JUDGE
#define debug(x) (cout<<(#x)<<':'<<(x)<<'\n')
#else
#define debug(x)
#endif
 
#define fast ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0)

template<typename temp>using ordered_set = tree<temp, null_type, less_equal<temp>, rb_tree_tag,tree_order_statistics_node_update>;
//order_of_key(k)  : Number of items strictly smaller than k .
//find_by_order(k) : K-th element in a set (counting from zero).//*(ost.find_by_order(k))

const ll MX = 1e18;
const ll mod = 1e9 + 7;

#define SZ 300003

vector <int> v[SZ];
 
int dis[SZ], low[SZ], col[SZ], ins[SZ], t, id;
 
stack <int> stk;

void BCC(int u, int p) {
 
    dis[u] = low[u] = ins[u] = ++t; stk.push(u);
 
    for(int x: v[u]) {
        if(!dis[x]) {
            BCC(x, u);
            low[u] = min(low[u], low[x]);
        } else if(ins[x] && p != x)
            low[u] = min(low[u], dis[x]);
    }
 
    if(dis[u] == low[u]) {
        ++id; int x;
        do {
            x = stk.top(); stk.pop();
            ins[x] = 0; col[x] = id;
        } while(x != u);
    }
}

map < pii, int > M;

void solve() {
    int n, m; cin >> n >> m;
    fe(i, 1, m) {
        int x, y, z; cin >> x >> y >> z;
        v[x].pb(y);
        v[y].pb(x);
        M[{x, y}] = z;
        M[{y, x}] = z;
    }
    int a, b; cin >> a >> b;
    v[a].pb(n + 1);
    v[n + 1].pb(a);
    v[b].pb(n + 1);
    v[n + 1].pb(b);
    BCC(1, 0);
    fe(i, 1, n) {
        if(col[a] != col[i]) continue;
        for(auto x : v[i]) {
            if(col[a] == col[x]) {
                if(M[{i, x}] == 1) {
                    cout << "YES" << N; return;
                } 
            }
        }
    }
    cout << "NO" << N;
}
//https://codeforces.com/contest/652/problem/E
int main() {
    // FILE;
    fast;
    // int t; cin >> t; while(t--)
    solve();
}
