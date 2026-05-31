#include <bits/stdc++.h>
#include <numeric>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    assert(1 <= n && n <= 100000);

    static int a[100010];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    static int diff[100010];
    adjacent_difference(a + 1, a + n + 1, diff + 1);

    // now diff[1] to diff[n] -> difference of a[1, n]

    // auto sp = span(diff + 2, n - 1) | views::filter([&](auto x) { return x > 0; }) | ranges::to<vector<int>>();
    // auto ans = accumulate(sp.begin(), sp.end(), 0);

    int ans = 0;
    for (int i = 2; i <= n; i++) {
        ans += diff[i] > 0 ? diff[i] : 0;
    }

    cout << ans << endl;
}