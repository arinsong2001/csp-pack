#include <bits/stdc++.h>

using namespace std;

int n, k;

struct Decl {
    int d, x, y;
};

auto ds = vector<Decl>{};

auto fa = vector<int>{};
auto d = vector<int>{};

int cnt = 0;

int find(int x) {
    if (fa[x] == x) { return x; }
    int root = find(fa[x]);
    d[x] = (d[x] + d[fa[x]]) % 3;
    return fa[x] = root;
}

void unite(int d, int x, int y) {
    int p = find(x), q = find(y);
    if (p == q) { return; }
    // ::d[x] + ::d[p] - ::d[y] === (d == 2) (% 3)
    // ::d[p] === (d == 2) + ::d[y] - ::d[x] (% 3)
    fa[p] = q, ::d[p] = (3 + (d == 2) + ::d[y] - ::d[x]) % 3;
}

void init() {
    for (int i = 0; i < k; i++) {
        int d, x, y;
        cin >> d >> x >> y;
        ds.push_back({d, x, y});
    }

    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);

    d.resize(n + 1);
}

bool check(int d, int x, int y) {
    if (x > n || y > n) { return false; }
    if (find(x) != find(y)) { return true; }
    return (3 + ::d[x] - ::d[y]) % 3 == (d == 2);
}

void operate(int d, int x, int y) {
    unite(d, x, y);
}

void solve() {
    for (auto [d, x, y] : ds) {
        if (!check(d, x, y)) {
            cnt++;
        } else {
            operate(d, x, y);
        }
    }
    cout << cnt << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n >> k;

    init();
    solve();
}