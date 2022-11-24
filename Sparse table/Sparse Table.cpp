struct Sparse {
    int n, lg;
    vector < vector < ll >> sparse_mx, sparse_mn, sparse_gcd;
    vector < ll > A;
    void init(int tmp) {
        n = tmp;
        A.resize(n+3);
        lg = 32 - __builtin_clz(n + 2); //64 if nmx > 10^9
        sparse_mx = vector < vector < ll >> (n + 2, vector<ll>(lg));
        sparse_gcd = vector < vector < ll >> (n + 2, vector<ll>(lg));
        sparse_mn = vector < vector < ll >> (n + 2, vector<ll>(lg));
    }

    void abr_init(ll aa[]) {
        for(int i = 1; i <= n; i++) A[i] = aa[i];
        build_table();
    }

    void build_table() {
        for(int i = 1; i <= n; i++) {
            sparse_mx[i][0] = A[i];
            sparse_mn[i][0] = A[i];
            sparse_gcd[i][0] = A[i];

        }
        for(int k = 1, p = 1; k < lg; k++, p <<= 1) {
            for(int i = 1; i + p + p <= n + 1; i++) {
                sparse_mn[i][k] = min(sparse_mn[i][k - 1], sparse_mn[i + p][k - 1]);
                sparse_mx[i][k] = max(sparse_mx[i][k - 1], sparse_mx[i + p][k - 1]);
                sparse_gcd[i][k] = __gcd(sparse_gcd[i][k - 1], sparse_gcd[i + p][k - 1]);
                
            }
        }
    }

    ll q_mn(int l, int r) {
        int len = r - l + 1;
        int k = 32 - __builtin_clz(len) - 1;
        return min(sparse_mn[l][k], sparse_mn[r - (1 << k) + 1][k]);
    }
    ll q_mx(int l, int r) {
        int len = r - l + 1;
        int k = 32 - __builtin_clz(len) - 1;
        return max(sparse_mx[l][k], sparse_mx[r - (1 << k) + 1][k]);
    }
    ll q_gcd(int l, int r) {
        int len = r - l + 1;
        int k = 32 - __builtin_clz(len) - 1;
        return __gcd(sparse_gcd[l][k], sparse_gcd[r - (1 << k) + 1][k]);
    }
};
