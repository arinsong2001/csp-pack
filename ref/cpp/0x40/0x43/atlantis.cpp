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
    int l, r;
    int dat, lazy;
};

int n, sz, id;

auto cs = vector<Chart>{};
auto ys = vector<double>{};
auto ids = unordered_map<double, int>{};
auto ls = vector<Line>{};
auto tr = vector<Node>{};

void build(int p, int l, int r) {
    tr[p].l = l, tr[p].r = r;
    if (l == r) { return; }
    int mid = l + (r - l) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
}

void propagate(int p) {
    if (tr[p].lazy) {
        tr[2 * p].dat += tr[p].lazy;
        tr[2 * p].lazy += tr[p].lazy;
        tr[2 * p + 1].dat += tr[p].lazy;
        tr[2 * p + 1].lazy += tr[p].lazy;
        tr[p].lazy = 0;
    }
}

double query(int p, int l, int r) {
    if (l <= tr[p].l && tr[p].r <= r) {
        if (tr[p].dat) { return ys[tr[p].r] - ys[tr[p].l - 1]; }
        if (tr[p].l == tr[p].r) { return 0; }
    }
    propagate(p);
    double ans = 0;
    if (l <= tr[2 * p].r) { ans += query(2 * p, l, r); }
    if (r >= tr[2 * p + 1].l) { ans += query(2 * p + 1, l, r); }
    return ans;
}

void operate(int p, int l, int r, int v) {
    if (l <= tr[p].l && tr[p].r <= r) {
        tr[p].dat += v;
        tr[p].lazy += v;
        return;
    }
    propagate(p);
    if (l <= tr[2 * p].r) { operate(2 * p, l, r, v); }
    if (r >= tr[2 * p + 1].l) { operate(2 * p + 1, l, r, v); }
    tr[p].dat = min(tr[2 * p].dat, tr[2 * p + 1].dat);
}

void init() {
    cs.clear();
    ys.clear();
    ids.clear();
    ls.clear();
    tr.clear();

    for (int i = 0; i < n; i++) {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cs.push_back({x1, y1, x2, y2});
        ys.push_back(y1), ys.push_back(y2);
    }

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    for (int i = 0; i < ys.size(); i++) { ids[ys[i]] = i; }

    for (int i = 0; i < cs.size(); i++) {
        auto [x1, y1, x2, y2] = cs[i];
        ls.push_back({x1, ids[y1] + 1, ids[y2], 1});
        ls.push_back({x2, ids[y1] + 1, ids[y2], -1});
    }
    sort(ls.begin(), ls.end(), [](const Line &l1, const Line &l2) { return l1.x != l2.x ? l1.x < l2.x : l1.v > l2.v; });

    sz = ys.size() - 1;
    tr.resize(4 * sz + 1);
    build(1, 1, sz);
}

void solve() {
    double area = 0;
    for (int i = 0; i < ls.size() - 1; i++) {
        auto [x, l, r, v] = ls[i];
        operate(1, l, r, v);
        double len = query(1, 1, sz);
        double height = ls[i + 1].x - x;
        area += len * height;
    }
    cout << "Test case #" << ++id << '\n';
    cout << "Total explored area: ";
    cout << fixed << setprecision(2) << area << "\n\n";
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