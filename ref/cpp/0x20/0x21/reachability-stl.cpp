#include <bits/stdc++.h>

using namespace std;

int n, m;

auto g = vector<vector<int>>{};

auto vs = set<int>{};

auto vis = vector<int>{};

bool has_cycle = false;

auto path = vector<int>{};

auto reach = vector<bitset<30010>>{};

void add(int u, int v) {
    vs.insert(u), vs.insert(v);
    g[u].push_back(v);
}

void dfs(int u) {
    vis[u] = 1;
    for (auto v : g[u]) {
        if (vis[v] == 1) {
            has_cycle = true;
            return;
        }
        if (vis[v] == 2) { continue; }
        dfs(v);
        if (has_cycle) { return; }
    }
    vis[u] = 2;
    path.push_back(u);
}

void init() {
    vis.resize(n + 1);
    reach.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        reach[i].set(i);
    }
}

void solve() {
    for (auto x : vs) {
        if (!vis[x]) { dfs(x); }
        if (has_cycle) { break; }
    }
    assert(!has_cycle);
    for (auto x : path) {
        for (auto y : g[x]) {
            reach[x] |= reach[y];
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << reach[i].count() << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n >> m;

    g.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
    }

    init();
    solve();
}