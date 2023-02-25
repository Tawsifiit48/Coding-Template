int seg[SZ][SZ], arr[SZ][SZ], n, m;

void build_y(int node1, int bx, int ex, int node2, int by, int ey) {
    if (by == ey) {
        if (bx == ex)
            seg[node1][node2] = arr[bx][by];
        else
            seg[node1][node2] = max(seg[node1*2][node2], seg[node1*2+1][node2]);
    } else {
        int mid_y = (by + ey) / 2;
        build_y(node1, bx, ex, node2*2, by, mid_y);
        build_y(node1, bx, ex, node2*2+1, mid_y+1, ey);
        seg[node1][node2] = max(seg[node1][node2*2], seg[node1][node2*2+1]);
    }
}

void build_x(int node, int bx, int ex) {
    if (bx != ex) {
        int mid_x = (bx + ex) / 2;
        build_x(node*2, bx, mid_x);
        build_x(node*2+1, mid_x+1, ex);
    }
    build_y(node, bx, ex, 1, 0, m-1);
}

void update_y(int node1, int bx, int ex, int node2, int by, int ey, int x, int y, int new_val) {
    if (by == ey) {
        if (bx == ex) {
            seg[node1][node2] = new_val;
        }
        else {
            seg[node1][node2] = max(seg[node1 * 2][node2], seg[node1 * 2 + 1][node2]);
        }
    } else {
        int mid_y = (by + ey) / 2;
        if (y <= mid_y) {
            update_y(node1, bx, ex, node2 * 2, by, mid_y, x, y, new_val);
        }
        else {
            update_y(node1, bx, ex, node2 * 2 + 1, mid_y + 1, ey, x, y, new_val);
        }
        seg[node1][node2] = max(seg[node1][node2 * 2], seg[node1][node2 * 2 + 1]);
    }
}

void update_x(int node, int bx, int ex, int x, int y, int new_val) {
    if (bx != ex) {
        int mid_x = (bx + ex) / 2;
        if (x <= mid_x) {
            update_x(node * 2, bx, mid_x, x, y, new_val);
        }
        else {
            update_x(node * 2 + 1, mid_x + 1, ex, x, y, new_val);
        }
    }
    update_y(node, bx, ex, 1, 0, m - 1, x, y, new_val);
}



int max_y(int node1, int node2, int by, int ey, int y1, int y2) {
    if (y1 > y2) {
        return 0;
    }
    if (y1 == by && ey == y2) {
        return seg[node1][node2];
    }
    int mid_y = (by + ey) / 2;
    return max(max_y(node1, node2 * 2, by, mid_y, y1, min(y2, mid_y)), max_y(node1, node2 * 2 + 1, mid_y + 1, ey, max(y1, mid_y + 1), y2));
}

int max_x(int node, int bx, int ex, int x1, int x2, int y1, int y2) {
    if (x1 > x2) {
        return 0;
    }
    if (x1 == bx && ex == x2) {
        return max_y(node, 1, 0, m-1, y1, y2);
    }
    int mid = (bx + ex) / 2;
    return max(max_x(node * 2, bx, mid, x1, min(x2, mid), y1, y2), max_x(node * 2 + 1, mid + 1, ex, max(x1, mid + 1), x2, y1, y2));
}

// set n = max_n + 1, m = max_m + 1
