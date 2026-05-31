#include <bits/stdc++.h>

using namespace std;

int n, k;

struct Decl {
    int d, x, y;
};

auto ds = vector<Decl>{};

auto fa = vector<int>{};

int cnt = 0;

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void unite(int x, int y) { fa[find(x)] = find(y); }

void init() {
    for (int i = 0; i < k; i++) {
        int d, x, y;
        cin >> d >> x >> y;
        ds.push_back({d, x, y});
    }

    fa.resize(3 * n + 1);
    for (int i = 1; i <= 3 * n; i++) { fa[i] = i; }
}

bool check(int d, int x, int y) {
    if (x > n || y > n) { return false; }
    if (d == 1 && (find(x + n) == find(y) || find(x) == find(y + n))) { return false; }
    if (d == 2 && (find(x) == find(y) || find(x) == find(y + n))) { return false; }
    return true;
}

void operate(int d, int x, int y) {
    if (d == 1) {
        if (find(x) == find(y)) { return; }
        unite(x, y);
        unite(x + n, y + n);
        unite(x + 2 * n, y + 2 * n);
    } else if (d == 2) {
        if (find(x + n) == find(y)) { return; }
        unite(x + n, y);
        unite(x + 2 * n, y + n);
        unite(x, y + 2 * n);
    } else {
        throw runtime_error("wrong d!");
    }
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