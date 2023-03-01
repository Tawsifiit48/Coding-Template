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

ll dp[21*SZ][2], cnt, sum[21*SZ];
void add(ll val) {
    int cur = 0;
    for(int i = 20; i >= 0; i--) {
        int id = checkBit(val, i);
        if(!dp[cur][id]) dp[cur][id] = ++cnt;
        cur = dp[cur][id];
        sum[cur]++;
    }
}
ll ans = 0;
int k;
void query(ll val, int cur, int msk, int flag) {
    if(msk == -1) {
        if(flag) {
            ans += sum[cur];
        }
        return;
    }
    int id1 = checkBit(val, msk);
    int id2 = checkBit(k, msk);
    if(flag) {
        ans += sum[cur];
        return;
    } else {
        if(id1 == 1 and id2 == 1) {
            if(dp[cur][0]) {
                query(val, dp[cur][0], msk - 1, flag);
            }
            if(dp[cur][1]) {    
                query(val, dp[cur][1], msk - 1, 1);
            }
        } else if(id1 == 1 and id2 == 0) {
            if(dp[cur][1]) {
                query(val, dp[cur][1], msk - 1, flag);
            }
        } else if(id1 == 0 and id2 == 1) {
            if(dp[cur][0]) {
                query(val, dp[cur][0], msk - 1, 1);
            }
            if(dp[cur][1]) {    
                query(val, dp[cur][1], msk - 1, flag);
            }
        } else {
            if(dp[cur][0]) {
                query(val, dp[cur][0], msk - 1, flag);
            }
        }
    }
}

void solve() {
    cnt = ans = 0;
    int n; cin >> n >> k;
    int arr[n + 10];
    fe(i, 1, n) {
        cin >> arr[i];
    }
    int xr = 0;
    add(0);
    fe(i, 1, n) {
        xr ^= arr[i];
        query(xr, 0, 20, 0);
        add(xr);
    }
    cout << ans << N;
    fe(i, 0, cnt) {
        dp[i][0] = dp[i][1] = sum[i] = 0;
    }
}

int main() {
    // FILE;
    fast;
    int t; cin >> t; while(t--)
    solve();
}
