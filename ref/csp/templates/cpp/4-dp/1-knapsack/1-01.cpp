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

    // vector<vector<int>> memo(N + 1, vector<int>(V + 1, -1));
    //
    // auto dfs = [&](auto &&self, int pos, int r) -> int {
    //     if (pos > N) {
    //         return 0;
    //     }
    //
    //     if (memo[pos][r] != -1) {
    //         return memo[pos][r];
    //     }
    //
    //     memo[pos][r] = self(self, pos + 1, r);
    //     if (r - v[pos] >= 0) {
    //         memo[pos][r] = max(memo[pos][r], self(self, pos + 1, r - v[pos]) + w[pos]);
    //     }
    //
    //     return memo[pos][r];
    // };
    //
    // cout << dfs(dfs, 0, V) << "\n";

    // vector<vector<int>> f(2, vector<int>(V + 1));
    //
    // for (int i = 1; i <= N; i++) {
    //     for (int j = 0; j <= V; j++) {
    //         f[i & 1][j] = f[i - 1 & 1][j];
    //     }
    //     for (int j = v[i]; j <= V; j++) {
    //         f[i & 1][j] = max(f[i - 1 & 1][j], f[i - 1 & 1][j - v[i]] + w[i]);
    //     }
    // }
    //
    // cout << f[N & 1][V] << "\n";

    vector<int> f(V + 1);

    for (int i = 1; i <= N; i++) {
        for (int j = V; j >= v[i]; j--) {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }

    cout << f[V] << "\n";
}
