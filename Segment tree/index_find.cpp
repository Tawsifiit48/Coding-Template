
void build(int node, int b, int e) {
    if(b == e) {
        seg[node] = arr[b]; //frequency of value b
        return;
    }
    int lt = node << 1;
    int rt = lt + 1;
    int mid = (b + e) / 2;
    build(lt, b, mid);
    build(rt, mid + 1, e);
    seg[node] = seg[rt] + seg[lt];
}

void update(int node, int b, int e, int i, int val) {
    if(b >= i and e <= i) {
        seg[node] += val;
        return;
    }
    if(b > i or e < i) return;
    int mid = (b + e) / 2;
    int lt = node << 1;
    int rt = lt + 1;
    update(lt, b, mid, i, val);
    update(rt, mid + 1, e, i, val);
    seg[node] = seg[rt] + seg[lt];
}
int query_k(int node, int b, int e, int k) {
    if(k > seg[node]) return -1;
    if(b == e) return b;
    int mid = (b + e) / 2;
    int lt = node << 1;
    int rt = lt + 1;
    if(seg[lt] >= k) {
        return query_k(lt, b, mid, k);
    } else return query_k(rt, mid + 1, e, k - seg[lt]);
}
