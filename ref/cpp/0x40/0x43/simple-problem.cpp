#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Node {
    int l, r;
    ll dat, lazy;
};

int n, m;

auto a = vector<ll>{};

auto tr = vector<Node>{};

void build(int p, int l, int r) {
    tr[p].l = l, tr[p].r = r;
    if (l == r) {
        tr[p].dat = a[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    tr[p].dat = tr[2 * p].dat + tr[2 * p + 1].dat;
}

void propagate(int p) {
    if (tr[p].lazy) {
        tr[2 * p].dat += tr[p].lazy * (tr[2 * p].r - tr[2 * p].l + 1);
        tr[2 * p + 1].dat += tr[p].lazy * (tr[2 * p + 1].r - tr[2 * p + 1].l + 1);
        tr[2 * p].lazy += tr[p].lazy;
        tr[2 * p + 1].lazy += tr[p].lazy;
        tr[p].lazy = 0;
    }
}

ll query(int p, int l, int r) {
    if (l <= tr[p].l && tr[p].r <= r) { return tr[p].dat; }
    propagate(p);
    ll ans = 0;
    if (l <= tr[2 * p].r) { ans += query(2 * p, l, r); }
    if (r >= tr[2 * p + 1].l) { ans += query(2 * p + 1, l, r); }
    return ans;
}

void operate(int p, int l, int r, ll v) {
    if (l <= tr[p].l && tr[p].r <= r) {
        tr[p].dat += v * (tr[p].r - tr[p].l + 1);
        tr[p].lazy += v;
        return;
    }
    propagate(p);
    if (l <= tr[2 * p].r) { operate(2 * p, l, r, v); }
    if (r >= tr[2 * p + 1].l) { operate(2 * p + 1, l, r, v); }
    tr[p].dat = tr[2 * p].dat + tr[2 * p + 1].dat;
}

void init() {
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) { cin >> a[i]; }

    tr.resize(4 * n + 1);
    build(1, 1, n);
}

void solve(int l, int r, ll d) {
    operate(1, l, r, d);
}

void solve(int l, int r) {
    cout << query(1, l, r) << '\n';
}

void solve() {
    for (int i = 0; i < m; i++) {
        char cmd;
        cin >> cmd;
        if (cmd == 'C') {
            int l, r;
            ll d;
            cin >> l >> r >> d;
            solve(l, r, d);
        } else if (cmd == 'Q') {
            int l, r;
            cin >> l >> r;
            solve(l, r);
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