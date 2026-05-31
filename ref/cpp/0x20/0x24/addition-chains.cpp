#include <bits/stdc++.h>

using namespace std;

int n;

auto x = vector<int>{};

int limit;

void init() {
    x.clear();
    x.resize(n + 1);
    x[1] = 1;
}

bool dfs(int pos) {
    if (pos > limit) { return false; }
    auto vis = vector<char>(n + 1);
    for (int i = pos - 1; i >= 1; i--) {
        for (int j = i; j >= 1; j--) {
            int tmp = x[i] + x[j];
            if (tmp > n || vis[tmp] || tmp <= x[pos - 1]) { continue; }
            vis[tmp] = true;
            x[pos] = tmp;
            if (x[pos] == n) { return true; }
            if (dfs(pos + 1)) { return true; }
            x[pos] = 0;
        }
    }
    return false;
}

void solve() {
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }
    for (limit = 2; limit <= n; limit++) {
        if (dfs(2)) {
            for (int i = 1; i <= limit; i++) {
                cout << x[i] << ' ';
            }
            cout << '\n';
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    while (cin >> n && n) {
        init();
        solve();
    }
}