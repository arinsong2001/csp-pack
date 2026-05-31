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
    vector<int> s(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> v[i] >> w[i] >> s[i];
    }

    // auto dfs = [&](auto &&self, int p, int r) -> int {
    //     if (p > N) {
    //         return 0;
    //     }
    //
    //     static vector<vector<int>> memo(N + 1, vector<int>(V + 1, -1));
    //
    //     if (memo[p][r] != -1) {
    //         return memo[p][r];
    //     }
    //
    //     int ans = self(self, p + 1, r);
    //
    //     for (int k = 1; k <= s[p]; k++) {
    //         if (r - k * v[p] < 0) {
    //             break;
    //         }
    //         ans = max(ans, self(self, p + 1, r - k * v[p]) + k * w[p]);
    //     }
    //
    //     return memo[p][r] = ans;
    // };
    //
    // cout << dfs(dfs, 1, V) << "\n";

    // vector<int> f(V + 1);
    //
    // for (int i = 1; i <= N; i++) {
    //     for (int j = V; j >= v[i]; j--) {
    //         for (int k = 1; k <= s[i]; k++) {
    //             if (j - k * v[i] < 0) {
    //                 break;
    //             }
    //             f[j] = max(f[j], f[j - k * v[i]] + k * w[i]);
    //         }
    //     }
    // }
    //
    // cout << f[V] << "\n";

    // vector<int> f(V + 1);
    //
    // for (int i = 1; i <= N; i++) {
    //     int k = 1;
    //     int left = s[i];
    //     while (k <= left) {
    //         int vi = v[i] * k;
    //         int wi = w[i] * k;
    //         for (int j = V; j >= vi; j--) {
    //             f[j] = max(f[j], f[j - vi] + wi);
    //         }
    //         left -= k;
    //         k <<= 1;
    //     }
    //     if (left > 0) {
    //         int vi = v[i] * left;
    //         int wi = w[i] * left;
    //         for (int j = V; j >= vi; j--) {
    //             f[j] = max(f[j], f[j - vi] + wi);
    //         }
    //     }
    // }
    //
    // cout << f[V] << "\n";

    constexpr int M = 20010;

    static int f[2][M];
    static int q[M];

    for (int i = 1; i <= N; i++) {
        for (int r = 0; r < v[i]; r++) {
            int hh = 0, tt = -1;
            for (int j = r; j <= V; j += v[i]) {
                while (hh <= tt && j - q[hh] > s[i] * v[i]) {
                    hh++;
                }
                while (hh <= tt && f[i - 1 & 1][q[tt]] + (j - q[tt]) / v[i] * w[i] <= f[i - 1 & 1][j]) {
                    tt--;
                }
                q[++tt] = j;
                f[i & 1][j] = f[i - 1 & 1][q[hh]] + (j - q[hh]) / v[i] * w[i];
            }
        }
    }

    cout << f[N & 1][V] << "\n";
}
