#include <bits/stdc++.h>

using namespace std;

int n, w, cats[20];

int cnt = 0, cabs[20];

int ans = 0x3f3f3f3f;

void dfs(int pos) {
    if (cnt >= ans) { return; }
    if (pos == n + 1) {
        ans = cnt;
        return;
    }
    for (int i = 1; i <= cnt; i++) {
        if (cabs[i] + cats[pos] > w) { continue; }
        cabs[i] += cats[pos];
        dfs(pos + 1);
        cabs[i] -= cats[pos];
    }
    cabs[++cnt] = cats[pos];
    dfs(pos + 1);
    cabs[cnt--] = 0;
}

void solve() {
    dfs(1);
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n >> w;
    for (int i = 1; i <= n; i++) { cin >> cats[i]; }

    ranges::sort(span(cats + 1, n), greater<>{});

    solve();
}