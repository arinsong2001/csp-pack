#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1010;

int n; // arr's size (1-based)

ll a[N];
ll tr[N << 2], tag[N << 2]; // tr: 区间和, tag: lazy（区间加）

// merge
void push_up(int u) {
    tr[u] = tr[u << 1] + tr[u << 1 | 1];
}

// propagation
void push_down(int u, int l, int r) {
    if (tag[u] == 0) {
        return;
    }

    int mid = (l + r) >> 1;

    // left child
    tr[u << 1] += tag[u] * (mid - l + 1);
    tag[u << 1] += tag[u];

    // right child
    tr[u << 1 | 1] += tag[u] * (r - mid);
    tag[u << 1 | 1] += tag[u];

    tag[u] = 0;
}

// 建树：build(1, 1, n)
void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    push_up(u);
}

// 区间加：[ql, qr] += v <=> update(1, 1, n, ql, qr, v)
void update(int u, int l, int r, int ql, int qr, ll v) {
    if (ql <= l && r <= qr) {
        tr[u] += v * (r - l + 1);
        tag[u] += v;
        return;
    }
    push_down(u, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        update(u << 1, l, mid, ql, qr, v);
    }
    if (qr > mid) {
        update(u << 1 | 1, mid + 1, r, ql, qr, v);
    }
    push_up(u);
}

// 区间查询
ll query(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tr[u];
    }
    push_down(u, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (ql <= mid) {
        res += query(u << 1, l, mid, ql, qr);
    }
    if (qr > mid) {
        res += query(u << 1 | 1, mid + 1, r, ql, qr);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
