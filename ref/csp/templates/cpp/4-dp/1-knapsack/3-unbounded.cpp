#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, V;
    cin >> N >> V;

    vector<int> v(N + 1);
    vector<int> w(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> v[i] >> w[i];
    }

    // auto dfs = [&](auto &&self, int r) -> int {
    //     if (r == 0) {
    //         return 0;
    //     }
    //
    //     static vector<int> memo(V + 1, -1);
    //
    //     if (memo[r] != -1) {
    //         return memo[r];
    //     }
    //
    //     int ans = 0;
    //     for (int i = 1; i <= N; i++) {
    //         if (r - v[i] < 0) {
    //             continue;
    //         }
    //         ans = max(ans, self(self, r - v[i]) + w[i]);
    //     }
    //
    //     return memo[r] = ans;
    // };
    //
    // cout << dfs(dfs, V) << "\n";

    // vector<vector<int>> f(2, vector<int>(V + 1));
    //
    // for (int i = 1; i <= N; i++) {
    //     for (int j = 0; j <= V; j++) {
    //         f[i & 1][j] = f[i - 1 & 1][j];
    //     }
    //     for (int j = v[i]; j <= V; j++) {
    //         f[i & 1][j] = max(f[i & 1][j], f[i & 1][j - v[i]] + w[i]);
    //     }
    // }
    //
    // cout << f[N & 1][V] << "\n";

    vector<int> f(V + 1);

    for (int i = 1; i <= N; i++) {
        for (int j = v[i]; j <= V; j++) {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }

    cout << f[V] << "\n";
}
