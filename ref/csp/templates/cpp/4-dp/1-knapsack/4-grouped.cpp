#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, V;
    cin >> N >> V;

    constexpr int max_n = 110;
    constexpr int max_s = 110;

    static int s[max_n];
    static int v[max_n][max_s];
    static int w[max_n][max_s];

    for (int i = 1; i <= N; i++) {
        cin >> s[i];
        for (int j = 1; j <= s[i]; j++) {
            cin >> v[i][j] >> w[i][j];
        }
    }

    vector<int> f(V + 1, -1);
    f[0] = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = V; j >= 0; j--) {
            for (int k = 1; k <= s[i]; k++) {
                if (j - v[i][k] >= 0) {
                    f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);
                }
            }
        }
    }

    cout << f[V] << "\n";
}
