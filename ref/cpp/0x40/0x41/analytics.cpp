#include <bits/stdc++.h>

using namespace std;

int t, n;

struct Bound {
    int i, j, e;
};

auto eqs = vector<Bound>{};
auto nes = vector<Bound>{};

auto vs = vector<int>{};
auto ids = unordered_map<int, int>{};

auto fa = vector<int>{};

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void unite(int x, int y) { fa[find(x)] = find(y); }

void init() {
    eqs.clear();
    nes.clear();

    vs.clear();
    ids.clear();

    for (int k = 0; k < n; k++) {
        int i, j, e;
        cin >> i >> j >> e;
        vs.push_back(i);
        vs.push_back(j);
        if (e) {
            eqs.push_back({i, j, e});
        } else {
            nes.push_back({i, j, e});
        }
    }

    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());
    for (int i = 0; i < vs.size(); i++) { ids[vs[i]] = i; }

    fa.clear();
    fa.resize(vs.size());
    for (int i = 0; i < fa.size(); i++) { fa[i] = i; }
}

void solve() {
    for (auto [i, j, _] : eqs) { unite(ids[i], ids[j]); }
    for (auto [i, j, _] : nes) {
        if (find(ids[i]) == find(ids[j])) {
            cout << "NO" << '\n';
            return;
        }
    }
    cout << "YES" << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> t;

    while (t--) {
        cin >> n;
        init();
        solve();
    }
}