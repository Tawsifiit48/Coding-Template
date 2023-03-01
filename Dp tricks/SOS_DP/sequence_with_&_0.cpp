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

// https://codeforces.com/contest/449/problem/D

ll dp[1 << 20], pw[1 << 20];

void solve() {
    int n; cin >> n;
    fe(i, 1, n) {
        int x; cin >> x;
        dp[x]++;
    }
    // dp[mask] = jotovabe (&) kore ami mask e ashte parbo
    int mx = (1 << 20) - 1;
    for(int i = 0; i <= 20; i++) {
        for(int mask = mx; mask >= 0; mask--) {
            if(checkBit(mask, i)) {
                dp[mask ^ (1 << i)] += dp[mask];
                if(dp[mask ^ (1 << i)] >= mod) {
                    dp[mask ^ (1 << i)] -= mod;
                }
            }
        }
    }
    pw[0] = 1;
    for(int i = 1; i <= mx; i++) {
        pw[i] = pw[i - 1] * 2;
        if(pw[i] >= mod) pw[i] -= mod;
    }

    ll ans = (pw[n] - 1 + mod) % mod;
    // just ami bad ditesi jader mask >= 0
    // ekhn suppose 11 ase. so amar oke bad dite hoile
    // duibar bad jacche . 0th and 1th bit er time e /exclusion
    // so jokhon 2 bit e on thakbe ami inclusion korbo
    for(int mask = 1; mask <= mx; mask++) {
        int cnt = __builtin_popcount(mask);
        if(cnt & 1) {
            ll temp = (pw[dp[mask]] - 1 + mod) % mod;
            ans = (ans + mod - temp) % mod;
        } else {
            ll temp = (pw[dp[mask]] - 1 + mod) % mod;
            ans = (ans + temp) % mod;
        }
    }
    cout << ans << N;
}

int main() {
    // FILE;
    fast;
    // int t; cin >> t; while(t--)
    solve();
}
