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

bool checkBit(ll n, ll i)
{
    return (n&(1LL<<i));
}
ll setBit(ll n, ll i)
{
    return (n|(1LL<<i));
}
ll resetBit(ll n, ll i)
{
    return (n&(~(1LL<<i)));
}

#define fast ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0)

template<typename temp>using ordered_set = tree<temp, null_type, less_equal<temp>, rb_tree_tag,tree_order_statistics_node_update>;
//order_of_key(k)  : Number of items strictly smaller than k .
//find_by_order(k) : K-th element in a set (counting from zero).//*(ost.find_by_order(k))

const ll MX = 1e18;
const ll mod = 1e9 + 7;

#define SZ 1000010

ll dp[SZ][2], cnt;

void add(ll val) {
    int cur = 0;
    for(int i = 34; i >= 0; i--) {
        int id = checkBit(val, i);
        if(!dp[cur][id]) dp[cur][id] = ++cnt;
        cur = dp[cur][id];
    }
}

ll querymin(ll val) {
    int cur = 0;
    ll ans = 0;
    for(int i = 34; i >= 0; i--) {
        int id = checkBit(val, i);
        if(dp[cur][id]) cur = dp[cur][id];
        else {
            ans |= 1 << i;
            cur = dp[cur][id ^ 1];
        }
    }
    return ans;
}

ll querymax(ll val) {
    int cur = 0;
    ll ans = 0;
    for(int i = 34; i >= 0; i--) {
        int id = checkBit(val, i);
        if(dp[cur][id ^ 1]) {
            ans |= 1 << i;
            cur = dp[cur][id ^ 1];
        } else {
            cur = dp[cur][id];
        }
    }
    return ans;
}
int cs;

void solve() {
    int n; cin >> n;
    ll arr[n + 10];
    fe(i, 1, n) {
        cin >> arr[i];
    }

    add(0);
    ll temp = 0;
    ll mn = 1e18, mx = 0;
    fe(i, 1, n) {
        temp ^= arr[i];
        mx = max(mx, querymax(temp));
        mn = min(mn, querymin(temp));
        add(temp);
    }
    cout << "Case " << ++cs << ": ";
    cout << mx << S << mn << N;
    cnt = 0;
    mem(dp);
}


int main()
{
    // FILE;
    fast;
    int t; cin >> t; while(t--)
    solve();
}
