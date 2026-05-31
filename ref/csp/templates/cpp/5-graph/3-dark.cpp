#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1);
    vector<int> w(n + 1);

    int u, v;

    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int root = 1;

    const int LOG = 32 - __builtin_clz(n);

    vector<vector<int>> fa(n + 1, vector<int>(LOG));
    vector<int> dep(n + 1);

    auto init = [&](auto &&self, int u, int p) -> void {
        fa[u][0] = p;
        dep[u] = dep[p] + 1;

        for (int i = 1; i < LOG; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }

        for (const auto &v : g[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u);
        }
    };

    init(init, root, 0);

    auto lca = [&](int x, int y) -> int {
        if (dep[x] < dep[y]) {
            swap(x, y);
        }

        for (int i = LOG - 1; i >= 0; i--) {
            if (dep[fa[x][i]] >= dep[y]) {
                x = fa[x][i];
            }
        }

        if (x == y) {
            return x;
        }

        for (int i = LOG - 1; i >= 0; i--) {
            if (fa[x][i] != fa[y][i]) {
                x = fa[x][i];
                y = fa[y][i];
            }
        }

        return fa[x][0];
    };

    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        w[u] += 1;
        w[v] += 1;
        int p = lca(u, v);
        w[p] -= 2;
    }

    int zeros = 0, ones = 0;

    vector<char> vis(n + 1);

    auto dfs = [&](auto &&self, int u) -> void {
        vis[u] = true;

        for (const auto &v : g[u]) {
            if (vis[v]) {
                continue;
            }
            self(self, v);
            w[u] += w[v];

            if (w[v] == 0) {
                zeros++;
            }
            if (w[v] == 1) {
                ones++;
            }
        }
    };

    dfs(dfs, root);

    int ans = zeros * m + ones;

    cout << ans << "\n";
}
