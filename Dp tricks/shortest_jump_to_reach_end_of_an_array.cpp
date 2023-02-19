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

#define SZ 100003

struct Sparse {
    int n, lg;
    vector < vector < pll >> sparse_mx;
    vector < pll > A;
    void init(int tmp) {
        n = tmp;
        A.resize(n+3);
        lg = 32 - __builtin_clz(n + 2); //64 if nmx > 10^9
        sparse_mx = vector < vector < pll >> (n + 2, vector<pll>(lg));
    }

    void abr_init(pll aa[]) {
        for(int i = 1; i <= n; i++) A[i] = aa[i];
        build_table();
    }

    void build_table() {
        for(int i = 1; i <= n; i++) {
            sparse_mx[i][0] = A[i];

        }
        for(int k = 1, p = 1; k < lg; k++, p <<= 1) {
            for(int i = 1; i + p + p <= n + 1; i++) {
                sparse_mx[i][k] = max(sparse_mx[i][k - 1], sparse_mx[i + p][k - 1]);
            }
        }
    }

    pll q_mx(int l, int r) {
        int len = r - l + 1;
        int k = 32 - __builtin_clz(len) - 1;
        return max(sparse_mx[l][k], sparse_mx[r - (1 << k) + 1][k]);
    }
    
};

ll dp[SZ];
pll arr[SZ];
// (i + 1)......m.......arr[i].xx..........n
// for i + 1 to mxind (mxind - i); one ticket enough
// for mxind + 1 to n (n - arr[i].xx);
// where is range(m + 1 to arr[i].xx);
// it is inside dp[m][j] for j -> mxind + 1 to arr[i].xx dp[m][j] = 1 as dp[i][j] should be


//link : https://codeforces.com/contest/675/problem/E

void solve() {
    int n;
    cin >> n;
    fe(i, 1, n - 1) {
        cin >> arr[i].xx;
        arr[i].yy = i;
    }
    arr[n] = {n, n};
    Sparse sp;
    sp.init(n); sp.abr_init(arr);

    dp[n] = 0;
    ll ans = 0;
    // dp[i] knows shortest route. so search for the maximum dp[i]
    for(int i = n - 1; i >= 1; i--) {
        pll mx = sp.q_mx(i + 1, arr[i].xx);
        dp[i] = (dp[mx.yy] + (n - arr[i].xx)) + (mx.yy - i);
        ans += dp[i];
    }
    cout << ans << N;
}

int main() {
    // FILE;
    fast;
    // int t; cin >> t; while(t--)
    solve();
}
