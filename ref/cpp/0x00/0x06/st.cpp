#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto arr = views::iota(1, 11) | ranges::to<vector<int>>();
    ranges::shuffle(arr, mt19937());

    auto show = [&](span<int> sp) {
        ranges::for_each(sp, [&](auto x) { cout << x << ' '; });
        cout << endl;
    };

    // show(arr);

    // F[i][j] maintains arr[i, i + 2**j - 1]
    // F[i][j] = max(F[i][j - 1], F[i + 2**(j - 1)][j - 1])

    // bl aka bit length
    auto bl = [&](const auto &x) {
        using T = decay_t<decltype(x)>;
        assert(x > 0);
        if constexpr (sizeof(T) <= 4) {
            return 32 - __builtin_clz(x);
        } else {
            return 64 - __builtin_clzll(x);
        }
    };

    auto prewarm = [&](const auto &arr) {
        int n = arr.size(), m = bl(n);
        vector<vector<int>> f(n, vector<int>(m));

        for (int i = 0; i < n; i++) {
            f[i][0] = arr[i];
        }

        for (int j = 1; j < m; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            }
        }

        return f;
    };

    auto query = [&](const vector<vector<int>> &f, int l, int r) {
        int k = bl(r - l + 1) - 1;
        return max(f[l][k], f[r - (1 << k) + 1][k]);
    };

    auto f = prewarm(arr);

    assert(query(f, 0, arr.size() - 1) == 10);
}