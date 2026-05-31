#include <bits/stdc++.h>

using namespace std;

struct Chart {
    double x1, y1, x2, y2;
};

struct Line {
    double x;
    int l, r, v;
};

struct Node {
    unique_ptr<Node> l, r;
    int dat, lazy;
};

int n, sz, id;

auto cs = vector<Chart>{};
auto ys = vector<double>{};
auto ids = unordered_map<double, int>{};
auto ls = vector<Line>{};
auto tr = unique_ptr<Node>{};

void propagate(unique_ptr<Node> &p, int l, int r) {
    if (!p) { return; }
    if (p->lazy) {
        if (!p->l) { p->l = make_unique<Node>(); }
        if (!p->r) { p->r = make_unique<Node>(); }
        int mid = l + (r - l) / 2;
        p->l->dat += p->lazy;
        p->l->lazy += p->lazy;
        p->r->dat += p->lazy;
        p->r->lazy += p->lazy;
        p->lazy = 0;
    }
}

double query(unique_ptr<Node> &p, int l, int r, int ql, int qr) {
    if (!p) { return 0; }
    if (ql <= l && r <= qr) {
        if (p->dat) { return ys.at(r) - ys.at(l - 1); }
        if (l == r) { return 0; }
    }
    propagate(p, l, r);
    int mid = l + (r - l) / 2;
    double ans = 0;
    if (ql <= mid) { ans += query(p->l, l, mid, ql, qr); }
    if (qr > mid) { ans += query(p->r, mid + 1, r, ql, qr); }
    return ans;
}

void operate(unique_ptr<Node> &p, int l, int r, int ql, int qr, int v) {
    if (!p) { return; }
    if (ql <= l && r <= qr) {
        p->dat += v;
        p->lazy += v;
        return;
    }
    propagate(p, l, r);
    int mid = l + (r - l) / 2;
    if (ql <= mid) {
        if (!p->l) { p->l = make_unique<Node>(); }
        operate(p->l, l, mid, ql, qr, v);
    }
    if (qr > mid) {
        if (!p->r) { p->r = make_unique<Node>(); }
        operate(p->r, mid + 1, r, ql, qr, v);
    }
    p->dat = min((p->l ? p->l->dat : 0), (p->r ? p->r->dat : 0));
}

void init() {
    cs.clear();
    ys.clear();
    ids.clear();
    ls.clear();

    for (int i = 0; i < n; i++) {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cs.push_back({x1, y1, x2, y2});
        ys.push_back(y1), ys.push_back(y2);
    }

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    for (int i = 0; i < ys.size(); i++) { ids.insert({ys.at(i), i + 1}); }

    for (int i = 0; i < cs.size(); i++) {
        auto [x1, y1, x2, y2] = cs[i];
        ls.push_back({x1, ids.at(y1), ids.at(y2) - 1, 1});
        ls.push_back({x2, ids.at(y1), ids.at(y2) - 1, -1});
    }
    sort(ls.begin(), ls.end(), [](const Line &l1, const Line &l2) { return l1.x != l2.x ? l1.x < l2.x : l1.v > l2.v; });

    sz = ys.size() - 1;
    tr = make_unique<Node>();
}

void solve() {
    double ans = 0;
    for (int i = 0; i < ls.size() - 1; i++) {
        auto [x, l, r, v] = ls.at(i);
        operate(tr, 1, sz, l, r, v);
        auto length = query(tr, 1, sz, 1, sz);
        auto height = ls[i + 1].x - x;
        ans += length * height;
    }
    cout << "Test case #" << ++id << '\n';
    cout << "Total explored area: ";
    cout << fixed << setprecision(2) << ans << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    while (cin >> n && n) {
        init();
        solve();
    }
}