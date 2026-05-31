#include <bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 1010;

int n; // arr's size (1-based)

ll a[N];
ll tr[N << 2]; // 4 * N

// 建树：build(1, 1, n)
void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    tr[u] = tr[u << 1] + tr[u << 1 | 1];
}

// 单点加：a[pos] += v <=> update(1, 1, n, pos, v)
void update(int u, int l, int r, int pos, ll v) {
    if (l == r) {
        tr[u] += v;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        update(u << 1, l, mid, pos, v);
    } else {
        update(u << 1 | 1, mid + 1, r, pos, v);
    }
    tr[u] = tr[u << 1] + tr[u << 1 | 1];
}

// 区间查询：query(1, 1, n, l, r)
ll query(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tr[u];
    }
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
