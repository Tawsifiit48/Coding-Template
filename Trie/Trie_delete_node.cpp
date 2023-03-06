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

int dp[42 * SZ][2], sum[42 * SZ], cnt;

void add(ll x) {
    int crt = 0;
    for(ll i = 41; i >= 0; i--) {
        int id = checkBit(x, i);
        if(!dp[crt][id]) {
            dp[crt][id] = ++cnt;
        }
        crt = dp[crt][id];
        sum[crt]++;
    }
}

void del(ll x) {
    int crt = 0;
    for(int i = 41; i >= 0; i--) {
        int id = checkBit(x, i);
        int nxt_crt = dp[crt][id];
        if(sum[nxt_crt] == 1) {
            dp[crt][id] = 0;
        }
        sum[nxt_crt]--;
        crt = nxt_crt;
    }
}

ll query(ll x) {
    int cur = 0;
    ll val = 0;
    for(ll i = 41; i >= 0; i--) {
        int id = checkBit(x, i);
        if(dp[cur][id ^ 1]) {
            if(id == 0) {
                val |= (1LL << i);
            }
            cur = dp[cur][id ^ 1];
        } else {
            if(id == 1) {
                x = resetBit(x, i);
            }
            cur = dp[cur][id];
        }
    }
    return val ^ x;
}
// https://codeforces.com/contest/282/problem/E
void solve() {
    int n; cin >> n;
    ll arr[n + 10];
    fe(i, 1, n) {
        cin >> arr[i];
    }
    ll pref[n + 10];
    pref[0] = 0;
    add(0);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] ^ arr[i];
        add(pref[i]);
        ans = max(ans, pref[i]);
    }
    ll crt = 0;
    for(int i = n; i >= 1; i--) {
        del(pref[i]);
        crt ^= arr[i];
        ans = max(ans, query(crt));
        ans = max(ans, crt);
    }
    ans = max(ans, crt);
    cout << ans << N;
}

int main() {
    // FILE;
    fast;
    // int t; cin >> t; while(t--)
    solve();
}
