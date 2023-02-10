#include<bits/stdc++.h>
using namespace std;
 
#define ll long long int
 
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
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
 
 
 
#define f(i, c, n) for(int i = c; i < n; i++)
#define fe(i, c, n) for(int i = c; i <= n; i++)
#define fr(i, n, c) for(int i = n - 1; i >= c; i--)
 
#define be(a) a.begin(), a.end()
#define rbe(a) a.rbegin(), a.rend()
#define vsort(a) sort(a.begin(), a.end())
#define mem(a) memset(a, 0, sizeof(a))
#define memn(a) memset(a, -1, sizeof(a))
#define srti(a, n) sort(a, a + n)
#define srtd(a, n) sort(a, a + n, greater<int>())
#define LB(a, x) (lower_bound(be(a), x) - a.begin())
#define UB(a, x) (upper_bound(be(a), x) - a.begin())
#define S " "
#define N "\n"
 
bool checkBit(ll n, ll i){ return (n&(1LL<<i)); }
ll setBit(ll n, ll i){ return (n|(1LL<<i)); }
ll resetBit(ll n, ll i){ return (n&(~(1LL<<i))); }
 
#define si(a) scanf("%d", &a)
#define sl(a) scanf("%lld", &a)
#define sii(a, b) scanf("%d %d", &a, &b)
#define sll(a, b) scanf("%lld %lld", &a, &b)
 
//cout << "Case " << ++cs << ": " <<
#define fast ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define FILE freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#define MXN 100002
#define LG 18

int n, sp[MXN][LG], spmx[MXN][LG], spmn[MXN][LG], lvl[MXN], cs;
vp v[MXN];

void dfs(int u, int p) {
    sp[u][0] = p;
    lvl[u] = lvl[p] + 1;
    for(auto x : v[u]) {
        if(x.xx == p) continue;
        spmx[x.xx][0] = x.yy;
        spmn[x.xx][0] = x.yy; 
        dfs(x.xx, u);
    }
}



void SPBL(int n) {

    for(int j = 1; (1 << j) <= n; j++) {
        for(int i = 1; i <= n; i++) {
            if(sp[i][j - 1] != -1) {
                spmx[i][j] = max(spmx[i][j - 1], spmx[sp[i][j - 1]][j - 1]);
                spmn[i][j] = min(spmn[i][j - 1], spmn[sp[i][j - 1]][j - 1]);
                sp[i][j] = sp[sp[i][j - 1]][j - 1];
            }
        }
    }
}

pii lca(int x, int y) {
    if(lvl[x] > lvl[y]) {
        swap(x, y);
    }
    pii ans = {0, 1e9};
    int dis = lvl[y] - lvl[x];
    for(int i = 17; i >= 0; i--) {
        if((1 << i) & dis) {
            ans.xx = max(spmx[y][i], ans.xx);
            ans.yy = min(spmn[y][i], ans.yy);
            y = sp[y][i];
            dis -= (1<<i);
        }
    }
    if(x == y) {
        return ans;
    }

    for(int i = 17; i >= 0; i--) {
        if(sp[x][i] != sp[y][i]) {
            ans.xx = max(ans.xx, spmx[x][i]);
            ans.xx = max(ans.xx, spmx[y][i]);
            ans.yy = min(ans.yy, spmn[x][i]);
            ans.yy = min(ans.yy, spmn[y][i]);
            x = sp[x][i], y = sp[y][i];
        }
    }
    ans.xx = max(ans.xx, spmx[x][0]);
    ans.xx = max(ans.xx, spmx[y][0]);
    ans.yy = min(ans.yy, spmn[x][0]);
    ans.yy = min(ans.yy, spmn[y][0]);
    return ans;
}

void init() {
    for(int i = 0; i < MXN; i++) {
        v[i].clear();
        for(int j = 0; j < LG; j++) {
            spmx[i][j] = 0;
            spmn[i][j] = 1e9;
        }
    }
    mem(lvl);
    memn(sp);
}

void solve() {
    init();
    cin >> n;
    f(i, 1, n) {
        int x, y, z;
        cin >> x >> y >> z;
        v[x].pb({y, z});
        v[y].pb({x, z});
    } 
    memn(sp);
    mem(spmx);
    mem(spmn);
    dfs(1, 0);
    SPBL(n);
    int q; cin >> q;
    cout << "Case " << ++cs << ":\n";
    while(q--) {
        int x, y; cin >> x >> y;
        pii ans = lca(x, y);
        cout << ans.yy << S << ans.xx << N;
    }
}

int main() {
    // FILE;
    fast;
    int t; cin >> t; while(t--)
    solve();
} 
