#include <bits/stdc++.h>

using namespace std;

int n, m;

struct QA {
    int l, r;
    string ans;
};

auto qas = vector<QA>{};

auto vs = vector<int>{};
auto ids = unordered_map<int, int>{};

auto fa = vector<int>{};
auto d = vector<int>{};

int find(int x) {
    if (fa[x] == x) { return x; }
    int root = find(fa[x]);
    d[x] ^= d[fa[x]];
    return fa[x] = root;
}

void unite(int x, int y, int ans) {
    int p = find(x), q = find(y);
    if (p == q) { return; }
    fa[p] = q, d[p] = d[x] ^ d[y] ^ ans;
}

void init() {
    qas.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> qas[i].l >> qas[i].r >> qas[i].ans;
        vs.push_back(qas[i].l - 1);
        vs.push_back(qas[i].r);
    }

    // vs
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());

    // ids
    for (int i = 0; i < vs.size(); i++) { ids[vs[i]] = i; }

    // fa
    fa.resize(vs.size());
    for (int i = 0; i < fa.size(); i++) { fa[i] = i; }

    // d
    d.resize(fa.size());
}

void solve() {
    // l, r, even -> diff[l - 1] ~ diff[r] -> unite(l - 1, r)
    // l, r, odd -> diff[l - 1] !~ diff[r]

    int cnt = 0;

    for (auto [l, r, ans] : qas) {
        int x = ids[l - 1], y = ids[r];
        if (find(x) == find(y)) {
            if ((d[x] ^ d[y]) != (ans == "odd")) { break; }
        } else {
            unite(x, y, ans == "odd");
        }
        cnt++;
    }

    cout << cnt << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n >> m;

    init();
    solve();
}