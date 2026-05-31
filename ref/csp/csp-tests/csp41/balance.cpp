#include <bits/stdc++.h>

using namespace std;

int n;

auto a = vector<int>{};

void init() {
    a.resize(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; }
}

void solve() {
    int cnt = 0;
    for (const auto &x : a) {
        assert(x > 0);
        int leng = 32 - __builtin_clz(x);
        int ones = __builtin_popcount(x);
        cnt += leng == ones + ones;
    }
    cout << cnt << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    init();
    solve();
}