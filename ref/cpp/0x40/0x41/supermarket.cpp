#include <bits/stdc++.h>

using namespace std;

int n;

struct Goods {
    int p, d;
};

auto gs = vector<Goods>{};

auto fa = vector<int>{};

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void unite(int x, int y) { fa[find(x)] = find(y); }

void init() {
    gs.clear();
    for (int i = 0; i < n; i++) {
        int p, d;
        cin >> p >> d;
        gs.push_back({p, d});
    }
    sort(gs.begin(), gs.end(), [](const Goods &x, const Goods &y) { return x.p > y.p; });
    int max_d = n ? max_element(gs.begin(), gs.end(), [](const Goods &x, const Goods &y) { return x.d < y.d; })->d : 0;
    fa.clear();
    fa.resize(max_d + 1);
    for (int i = 0; i < fa.size(); i++) { fa[i] = i; }
}

void solve() {
    int ans = 0;
    for (auto [p, d] : gs) {
        int r = find(d);
        if (r) {
            ans += p;
            unite(r, r - 1);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    while (cin >> n) {
        init();
        solve();
    }
}