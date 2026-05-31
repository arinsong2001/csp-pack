#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Star {
    ll x, y;
    int c;
};

struct Line {
    ll x;
    int l, r, v;
};

struct Node {
    int l, r;
    int dat, lazy;
};

int n, w, h, sz;

auto ss = vector<Star>{};
auto ys = vector<ll>{};
auto ids = unordered_map<ll, int>{};
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

int query(int p, int l, int r) {
    if (l <= tr[p].l && tr[p].r <= r) { return tr[p].dat; }
    propagate(p);
    int ans = 0;
    if (l <= tr[2 * p].r) { ans = max(ans, query(2 * p, l, r)); }
    if (r >= tr[2 * p + 1].l) { ans = max(ans, query(2 * p + 1, l, r)); }
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
    tr[p].dat = max(tr[2 * p].dat, tr[2 * p + 1].dat);
}

void init() {
    ss.clear();
    ys.clear();
    ids.clear();
    ls.clear();
    tr.clear();

    for (int i = 0; i < n; i++) {
        ll x, y;
        int c;
        cin >> x >> y >> c;
        ss.push_back({x, y, c});
        ys.push_back(y), ys.push_back(y + h - 1);
    }

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    for (int i = 0; i < ys.size(); i++) { ids[ys[i]] = i + 1; }

    for (int i = 0; i < ss.size(); i++) {
        auto [x, y, c] = ss[i];
        ls.push_back({x, ids[y], ids[y + h - 1], c});
        ls.push_back({x + w - 1, ids[y], ids[y + h - 1], -c});
    }
    sort(ls.begin(), ls.end(), [](const Line &l1, const Line &l2) { return l1.x != l2.x ? l1.x < l2.x : l1.v > l2.v; });

    sz = ys.size();
    tr.resize(4 * sz + 1);
    build(1, 1, sz);
}

void solve() {
    int light = 0;
    for (int i = 0; i < ls.size(); i++) {
        auto [x, l, r, v] = ls[i];
        operate(1, l, r, v);
        light = max(light, query(1, 1, sz));
    }
    cout << light << '\n';
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