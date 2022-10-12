int lazy[SZ], st[SZ], arr[SZ];

inline void push(int node, int b, int e) {
    if (lazy[node] == 0) return;
    st[node] = st[node] + lazy[node] * (e - b + 1);
    if (b != e) {
        int l = node << 1;
        int r = l + 1;
        lazy[l] = lazy[l] + lazy[node];
        lazy[r] = lazy[r] + lazy[node];
    }
    lazy[node] = 0;
}

inline long long combine(long long a,long long b) {
    return a + b;
}

inline void pull(int node) {
    st[node] = st[node << 1] + st[(node << 1) | 1];
}

void build(int node, int b, int e) {
    lazy[node] = 0;
    if (b == e) {
        st[node] = arr[b];
        return;
    }
    int mid = (b + e) >> 1;
    int l = node << 1;
    int r = l + 1;
    build(l, b, mid);
    build(r, mid + 1, e);
    pull(node);
}
void upd(int node, int b, int e, int i, int j, long long v) {
    push(node, b, e);
    if(j < b || e < i) return;
    if(i <= b && e <= j) {
        lazy[node] = v; //set lazy
        push(node, b, e);
        return;
    }
    int mid = (b + e) >> 1;
    int l = node << 1;
    int r = l + 1;
    upd(l, b, mid, i, j, v);
    upd(r, mid + 1, e, i, j, v);
    pull(node);
}

long long query(int node, int b, int e, int i, int j) {
    push(node, b, e);
    if (i > e || b > j) return 0;
    if (i <= b && e <= j) return st[node];
    int mid = (b + e) >> 1;
    int l = node << 1;
    int r = l + 1;
    return combine(query(l, b, mid, i, j), query(r, mid + 1, e, i, j));
}
