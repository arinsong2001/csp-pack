#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int w, n;

auto g = vector<int>{};

auto cab1 = vector<int>{};
auto cab2 = vector<int>{};

int ans = 0;

void dfs(int pos, int end, ll curr_w, vector<int> &cab) {
    if (pos > end) {
        cab.push_back(curr_w);
        return;
    }
    dfs(pos + 1, end, curr_w, cab);
    if (curr_w + g[pos] <= w) { dfs(pos + 1, end, curr_w + g[pos], cab); }
}

void solve() {
    int mid = (1 + n) / 2;
    dfs(1, mid, 0, cab1);
    dfs(mid + 1, n, 0, cab2);

    sort(cab1.begin(), cab1.end());
    cab1.erase(unique(cab1.begin(), cab1.end()), cab1.end());
    sort(cab2.begin(), cab2.end());
    cab2.erase(unique(cab2.begin(), cab2.end()), cab2.end());

    for (auto x : cab1) {
        int y = w - x;
        auto it = upper_bound(cab2.begin(), cab2.end(), y);
        int z = it == cab2.begin() ? 0 : *prev(it);
        ans = max(ans, x + z);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("1.in", "r", stdin);

    cin >> w >> n;

    g.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> g[i];
    }
    sort(g.begin() + 1, g.begin() + n + 1, greater<>{});

    solve();
}