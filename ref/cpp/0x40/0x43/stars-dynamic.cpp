#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Star {
    ll x, y, c;
};

struct Line {
    ll x, l, r, v;
};

struct Node {
    unique_ptr<Node> l, r;
    ll dat, lazy;
};

ll n, w, h, sz;

auto ss = vector<Star>{};
auto ys = vector<ll>{};
auto ids = unordered_map<ll, ll>{};
auto ls = vector<Line>{};
auto tr = unique_ptr<Node>{};

void propagate(unique_ptr<Node> &p, ll l, ll r) {
    assert(p);
    if (p->lazy) {
        if (!p->l) { p->l = make_unique<Node>(); }
        if (!p->r) { p->r = make_unique<Node>(); }
        p->l->dat += p->lazy;
        p->l->lazy += p->lazy;
        p->r->dat += p->lazy;
        p->r->lazy += p->lazy;
        p->lazy = 0;
    }
}

ll query(unique_ptr<Node> &p, ll l, ll r, ll ql, ll qr) {
    if (!p) { return 0; }
    if (ql <= l && r <= qr) { return p->dat; }
    propagate(p, l, r);
    ll mid = l + (r - l) / 2;
    ll ans = 0;
    if (ql <= mid) { ans += query(p->l, l, mid, ql, qr); }
    if (qr > mid) { ans += query(p->r, mid + 1, r, ql, qr); }
    return ans;
}

void operate(unique_ptr<Node> &p, ll l, ll r, ll ql, ll qr, ll v) {
    assert(p);
    if (ql <= l && r <= qr) {
        p->dat += v;
        p->lazy += v;
        return;
    }
    propagate(p, l, r);
    ll mid = l + (r - l) / 2;
    if (ql <= mid) {
        if (!p->l) { p->l = make_unique<Node>(); }
        operate(p->l, l, mid, ql, qr, v);
    }
    if (qr > mid) {
        if (!p->r) { p->r = make_unique<Node>(); }
        operate(p->r, mid + 1, r, ql, qr, v);
    }
    p->dat = max((p->l ? p->l->dat : 0), (p->r ? p->r->dat : 0));
}

void init() {
    ss.clear();
    ys.clear();
    ids.clear();
    ls.clear();

    for (int i = 0; i < n; i++) {
        ll x, y, c;
        cin >> x >> y >> c;
        ss.push_back({x, y, c});
        ys.push_back(y), ys.push_back(y + h - 1);
    }

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    for (int i = 0; i < ys.size(); i++) { ids.insert({ys.at(i), i + 1}); }

    for (int i = 0; i < ss.size(); i++) {
        auto [x, y, c] = ss.at(i);
        ls.push_back({x, ids.at(y), ids.at(y + h - 1), c});
        ls.push_back({x + w - 1, ids.at(y), ids.at(y + h - 1), -c});
    }
    sort(ls.begin(), ls.end(), [](const Line &l1, const Line &l2) { return l1.x != l2.x ? l1.x < l2.x : l1.v > l2.v; });

    sz = ys.size();
    tr = make_unique<Node>();
}

void solve() {
    ll ans = 0;
    for (int i = 0; i < ls.size(); i++) {
        auto [x, l, r, v] = ls[i];
        operate(tr, 1, sz, l, r, v);
        ans = max(ans, query(tr, 1, sz, 1, sz));
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    while (cin >> n >> w >> h) {
        init();
        solve();
    }
}