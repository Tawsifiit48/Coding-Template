int arr[SZ], block_size, ans[SZ], cs;
pair < pii, int > queries[SZ];
inline bool mo_cmp(const pair<pii, int > &x, const pair<pii, int> &y) {
    int block_x = x.xx.xx / block_size;
    int block_y = y.xx.xx / block_size;
    if(block_x != block_y) {
        return block_x < block_y;
    } 
    return x.xx.yy < y.xx.yy;
}
inline void add(int x) {
    
}
inline void remove(int x) {
    

}
void solve() {
    int n, m, q; cin >> n >> m >> q;
    block_size = static_cast<int>(sqrt(n));
    int cnt = 1;
    fe(i, 1, n) {
        cin >> arr[i];
    }
    for(int i = 1; i <= q; i++) {
        cin >> queries[i].xx.xx >> queries[i].xx.yy;
        queries[i].yy = i;
    }
    sort(queries + 1, queries + q + 1, mo_cmp);
    cout << "Case " << ++cs << ":\n";
    int mo_lt = 0, mo_rt = -1;
    for(int i = 1; i <= q; i++) {
        int lt = queries[i].xx.xx;
        int rt = queries[i].xx.yy;
        while(mo_rt < rt) {
            mo_rt++;
            add(arr[mo_rt]);
        }
        while(mo_rt > rt) {
            remove(arr[mo_rt]);
            mo_rt--;
        }
        while(mo_lt < lt) {
            remove(arr[mo_lt]);
            mo_lt++;
        }
        while(mo_lt > lt) {
            mo_lt--;
            add(arr[mo_lt]);
        }
        // ans[queries[i].yy] = ;
    }
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << N;
    }
    
}
int main() {
    // FILE;
    fast;
    int t; cin >> t; while(t--)
    solve();
}
