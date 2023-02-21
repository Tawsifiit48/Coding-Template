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

#define SZ 110

int n, m;
struct matrix
{
    ll mat[110][110];
 
    matrix(int x) {
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= m; j++) mat[i][j] = x;
        }
    }

    matrix operator*(const matrix& rhs)
    {
        matrix res(0);
 
        for(int i = 1; i <= m; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                for(int k = 1; k <= m; k++)
                {
                    ll p = (1LL*mat[i][k]*rhs.mat[k][j]);
                    if(p >= mod) p %= mod;
                    res.mat[i][j] += p;
                    if(res.mat[i][j] >= mod) {
                        res.mat[i][j] %= mod;
                    }
                }
            }
        }
 
        return res;
    }
 
} rec(0);
 
matrix powi()
{
    matrix res(1);
 
    while (n)
    {
        if (n & 1LL) res = res*rec;
 
        n >>= 1;
        rec = rec*rec;
    }
 
    return res;
}

//https://codeforces.com/contest/1117/problem/D

void solve() {
    cin >> n >> m;
    if(m > n) {
        cout << 1 << N; return;
    }    

    rec.mat[1][1] = rec.mat[1][m] = 1;
    fe(i, 2, m) {
        rec.mat[i][i - 1] = 1;
    }
    n = n - m;
    rec = powi();
    cout << rec.mat[1][1] << N;
}

int main() {
    // FILE;
    fast;
    // int t; cin >> t; while(t--)
    solve();
}
