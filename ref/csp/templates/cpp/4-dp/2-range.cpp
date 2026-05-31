// 区间DP
//
// LOJ P10147: NOI1995 石子合并
//
// example:
//
// input:
// 4
// 4 5 9 4
//
// output:
// 43
// 54

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<ll> b = a;
    b.insert(b.end(), a.begin(), a.end());

    vector<ll> pref(2 * n + 1);
    partial_sum(b.begin(), b.end(), pref.begin() + 1);

    const ll INF = numeric_limits<ll>::max();

    auto seek_min = [&]() {
        vector<vector<ll>> f(2 * n, vector<ll>(2 * n, INF));

        for (int i = 0; i < 2 * n; i++) {
            f[i][i] = 0;
        }

        for (int length = 2; length <= n; length++) {
            for (int i = 1; i <= 2 * n - length; i++) {
                int j = i + length - 1;
                for (int k = i; k < j; k++) {
                    auto tmp = f[i][k] + f[k + 1][j] + pref[j] - pref[i - 1];
                    f[i][j] = min(f[i][j], tmp);
                }
            }
        }

        ll ans = INF;
        for (int i = 1; i <= n; i++) {
            ans = min(ans, f[i][i + n - 1]);
        }

        return ans;
    };

    auto seek_max = [&]() {
        vector<vector<ll>> f(2 * n, vector<ll>(2 * n, 0));

        for (int length = 2; length <= n; length++) {
            for (int i = 1; i <= 2 * n - length; i++) {
                int j = i + length - 1;
                for (int k = i; k < j; k++) {
                    auto tmp = f[i][k] + f[k + 1][j] + pref[j] - pref[i - 1];
                    f[i][j] = max(f[i][j], tmp);
                }
            }
        }

        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = max(ans, f[i][i + n - 1]);
        }

        return ans;
    };

    cout << seek_min() << "\n";
    cout << seek_max() << "\n";
}
