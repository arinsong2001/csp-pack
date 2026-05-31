#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Node {
    int l, r;
    ll dat;
};

int n, m;

auto a = vector<ll>{};
auto b = vector<ll>{};

auto c = vector<ll>{};
auto tr = vector<Node>{};

namespace fen {

void build() {
    for (int i = 1; i <= n; i++) { c[i] = b[i]; }
    for (int i = 1; i <= n; i++) {
        int j = i + (i & -i);
        if (j <= n) { c[j] += c[i]; }
    }
}

ll query(int i) { return !i ? 0 : c[i] + query(i - (i & -i)); }

bool operate(int i, ll v) { return i > n ? true : (c[i] += v, operate(i + (i & -i), v)); }

bool r_operate(int l, int r, ll v) { return r + 1 <= n ? (operate(l, v), operate(r + 1, -v)) : operate(l, v); }

}; // namespace fen

namespace seg {

void build(int p, int l, int r) {
    tr[p].l = l, tr[p].r = r;
    if (l == r) {
        tr[p].dat = b[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    tr[p].dat = gcd(tr[2 * p].dat, tr[2 * p + 1].dat);
}

ll query(int p, int l, int r) {
    if (l > r) { return 0; }
    if (l <= tr[p].l && tr[p].r <= r) { return tr[p].dat; }
    ll ans = 0;
    if (l <= tr[2 * p].r) { ans = gcd(ans, query(2 * p, l, r)); }
    if (r >= tr[2 * p + 1].l) { ans = gcd(ans, query(2 * p + 1, l, r)); }
    return ans;
}

void operate(int p, int i, ll v) {
    if (tr[p].l == tr[p].r) {
        tr[p].dat += v;
        return;
    }
    if (i <= tr[2 * p].r) { operate(2 * p, i, v); }
    if (i >= tr[2 * p + 1].l) { operate(2 * p + 1, i, v); }
    tr[p].dat = gcd(tr[2 * p].dat, tr[2 * p + 1].dat);
}

void r_operate(int p, int l, int r, ll v) {
    operate(p, l, v);
    if (r + 1 <= n) { operate(p, r + 1, -v); }
}

}; // namespace seg

void init() {
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) { cin >> a[i]; }

    b.resize(n + 1);
    adjacent_difference(a.begin(), a.end(), b.begin());

    c.resize(n + 1);
    fen::build();

    tr.resize(4 * n + 1);
    seg::build(1, 1, n);
}

void solve(int l, int r, ll d) {
    fen::r_operate(l, r, d);
    seg::r_operate(1, l, r, d);
}

void solve(int l, int r) {
    cout << gcd(fen::query(l), seg::query(1, l + 1, r)) << '\n';
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