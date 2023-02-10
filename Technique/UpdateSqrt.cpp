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

#define SZ 500003

int arr[SZ];

struct SQRT_Decompose {
    vector < int > b[SZ];
    int len;

    void update(int ind, int x) {
        int lw = lower_bound(be(b[ind / len]), arr[ind]) - b[ind / len].begin();
        b[ind / len][lw] = x;
        sort(be(b[ind / len]));
        arr[ind] = x;

    }

    int query(int l, int r, int x) {
        int ans = 0;
        int c_l = l / len;
        int c_r = r / len;
        if(c_l == c_r) {
            for(int i = l; i <= r; i++) {
                if(arr[i] >= x) ans++;
            }
        } else {
            for (int i=l, end=(c_l+1)*len - 1; i<=end; ++i) {
                if(arr[i] >= x) ans++;
            }
            for (int i=c_r*len; i<=r; ++i) {
                if(arr[i] >= x) ans++;
            }
            for (int i=c_l+1; i<=c_r-1; ++i) {
                int lw = lower_bound(be(b[i]), x) - b[i].begin();
                ans += (int)b[i].size() - lw;
            }
        }
        return ans;
    }

    void preprocess(int n) {
        len = (int)sqrt(n + .0) + 1;
        for(int i = 0; i < n; i++) {
            b[i / len].pb(arr[i]);
        }

        for(int i = 0; i < len; i++) {
            sort(be(b[i]));
        }
    }

};

void solve() {
    int n; cin >> n;
    fe(i, 0, n-1) {
        cin >> arr[i];
    }
    SQRT_Decompose sd;

    sd.preprocess(n);
    int q; cin >> q;

    fe(i, 1, q) {
        int c; cin >> c;
        if(c == 0) {
            int x, y, z;
            cin >> x >> y >> z;
            x--, y--;
            cout << sd.query(x, y, z) << N;
        } else {
            int x, y; cin >> x >> y;
            x--;
            sd.update(x, y);
        }
    }
}

int main() {
    // FILE;
    fast;
    // int t; cin >> t; while(t--)
    solve();
}
