#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 3;
    vector<vector<pair<int, int>>> g(n);

    g[0].push_back(pair{1, 3});
    g[1].push_back(pair{0, 3});

    g[1].push_back(pair{2, 5});
    g[2].push_back(pair{1, 5});

    // <0> <--3--> <1> <--5--> <2>

    vector<int> f(n);
    vector<char> vis(n);
    int ans = 0;

    auto dp = [&](auto &&self, int u) -> void {
        vis[u] = true;
        for (auto [v, w] : g[u]) {
            if (vis[v]) {
                continue;
            }
            self(self, v);
            ans = max(ans, f[u] + f[v] + w);
            f[u] = max(f[u], f[v] + w);
        }
    };

    dp(dp, 0);
    cout << ans << endl;

    fill(vis.begin(), vis.end(), false);
    ans = 0;

    int dist = 0;
    int best_vert = -1;

    auto dfs = [&](auto &&self, int u) -> void {
        vis[u] = true;

        if (dist > ans) {
            ans = dist;
            best_vert = u;
        }

        for (auto [v, w] : g[u]) {
            if (vis[v]) {
                continue;
            }
            dist += w;
            self(self, v);
            dist -= w;
        }
    };

    dfs(dfs, 0);

    fill(vis.begin(), vis.end(), false);
    ans = 0;

    dfs(dfs, best_vert);

    cout << ans << endl;
}
