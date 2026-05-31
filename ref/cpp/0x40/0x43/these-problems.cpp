#include <bits/stdc++.h>

using namespace std;

struct Info {
    int sum, lmax, rmax, dat;
};

struct Node {
    int l, r;
    Info info;
};

int n, m;

auto a = vector<int>{};

auto tr = vector<Node>{};

Info merge(const Info &left, const Info &right) {
    Info res;
    res.sum = left.sum + right.sum;
    res.lmax = max(left.lmax, left.sum + right.lmax);
    res.rmax = max(right.rmax, right.sum + left.rmax);
    res.dat = max({left.dat, right.dat, left.rmax + right.lmax});
    return res;
}

void build(int p, int l, int r) {
    tr[p].l = l, tr[p].r = r;
    if (l == r) {
        tr[p].info = {a[l], a[l], a[l], a[l]};
        return;
    }
    int mid = (l + r) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    tr[p].info = merge(tr[2 * p].info, tr[2 * p + 1].info);
}

Info query(int p, int l, int r) {
    if (l <= tr[p].l && r >= tr[p].r) { return tr[p].info; }
    int mid = (tr[p].l + tr[p].r) / 2;
    if (r <= mid) { return query(2 * p, l, r); }
    if (l > mid) { return query(2 * p + 1, l, r); }
    return merge(query(2 * p, l, r), query(2 * p + 1, l, r));
}

void operate(int p, int i, int v) {
    if (tr[p].l == tr[p].r) {
        tr[p].info = {v, v, v, v};
        return;
    }
    int mid = (tr[p].l + tr[p].r) / 2;
    if (i <= mid) {
        operate(2 * p, i, v);
    } else {
        operate(2 * p + 1, i, v);
    }
    tr[p].info = merge(tr[2 * p].info, tr[2 * p + 1].info);
}

void init() {
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) { cin >> a[i]; }

    tr.resize(4 * n + 1);
    build(1, 1, n);
}

void solve() {
    for (int i = 0; i < m; i++) {
        int cmd, x, y;
        cin >> cmd >> x >> y;
        if (cmd == 1) {
            if (x > y) { swap(x, y); }
            cout << query(1, x, y).dat << '\n';
        } else if (cmd == 2) {
            operate(1, x, y);
        } else {
            throw runtime_error("wrong cmd!");
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n >> m;

    init();
    solve();
}