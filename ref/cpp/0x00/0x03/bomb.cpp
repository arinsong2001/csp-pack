#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, R;
    cin >> N >> R;

    vector<vector<int>> g(5002, vector<int>(5002));

    for (int i = 0; i < N; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        g[x + 1][y + 1] += w;
    }

    auto prefix2 = [&](auto &g) {
        for (int i = 1; i <= 5001; i++) {
            for (int j = 1; j <= 5001; j++) {
                g[i][j] += g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1];
            }
        }
    };

    prefix2(g);

    auto query = [&](int i, int j) {
        return g[i][j] - g[i - R][j] - g[i][j - R] + g[i - R][j - R];
    };

    int ans = 0;

    if (R < 5000) {
        for (int i = R; i < g.size(); i++) {
            for (int j = R; j < g[0].size(); j++) {
                ans = max(ans, query(i, j));
            }
        }
    } else {
        ans = g[5001][5001];
    }

    cout << ans << endl;
}