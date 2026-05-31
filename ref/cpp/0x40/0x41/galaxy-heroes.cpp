#include <bits/stdc++.h>

using namespace std;

int t;

struct CMD {
    char c;
    int i, j;
};

auto cs = vector<CMD>{};

int n = 0;

auto fa = vector<int>{};
auto d = vector<int>{};
auto sz = vector<int>{};

int find(int x) {
    if (fa[x] == x) { return x; }
    int root = find(fa[x]);
    d[x] += d[fa[x]];
    return fa[x] = root;
}

void unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) { return; }
    fa[x] = y, d[x] = sz[y];
    sz[y] += sz[x];
}

void init() {
    cs.resize(t);
    for (int i = 0; i < t; i++) {
        cin >> cs[i].c >> cs[i].i >> cs[i].j;
        n = max(n, max(cs[i].i, cs[i].j));
    }

    fa.resize(n + 1);
    for (int i = 1; i <= n; i++) { fa[i] = i; }

    d.resize(n + 1);

    sz.resize(n + 1);
    for (int i = 1; i <= n; i++) { sz[i] = 1; }
}

void solve() {
    for (auto [c, i, j] : cs) {
        if (c == 'M') {
            unite(i, j);
        } else if (c == 'C' && find(i) == find(j)) {
            cout << (i == j ? 0 : abs(d[i] - d[j]) - 1) << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> t;

    init();
    solve();
}