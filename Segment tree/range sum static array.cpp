#define SZ 100002
int seg[4*SZ], arr[SZ];

void build(int node, int b, int e) {
	if(b == e) {
		seg[node] = arr[b];
		return;
	}
	int lt = node << 1;
	int rt = lt + 1;
	int mid = (b + e) / 2;
	build(lt, b, mid);
	build(rt, mid + 1, e);
	seg[node] = seg[lt] + seg[rt];
}

void update(int node, int b, int e, int i, int newval) {
	if(i > e or i < b) {
		return;
	}
	if(b >= i and e <= i) {
		seg[node] = newval;
		return;
	}
	int lt = node << 1;
	int rt = lt + 1;
	int mid = (b + e) / 2;
	update(lt, b, mid, i, newval);
	update(rt, mid + 1, e, i, newval);
	seg[node] = seg[lt] + seg[rt];
}

int query(int node, int b, int e, int i, int j) {
	if(i > e or j < b) {
		return 0;
	}

	if(b >= i and e <= j) {
		return seg[node];
	}
	int lt = node << 1;
	int rt = lt + 1;
	int mid = (b + e) / 2;
	int p1 = 0, p2 = 0;
	p1 = query(lt, b, mid, i, j);
	p2 = query(rt, mid + 1, e, i, j);
	return p1 + p2;
}
