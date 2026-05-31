#include <bits/stdc++.h>

using namespace std;

int n, m;

auto r = vector<int>{};
auto h = vector<int>{};

auto min_v = vector<int>{};
auto min_s = vector<int>{};

int ans = 0x3f3f3f3f;

void init() {
    r.resize(m + 2);
    r[m + 1] = 0x3f3f3f3f;

    h.resize(m + 2);
    h[m + 1] = 0x3f3f3f3f;

    min_v.resize(m + 1);
    min_s.resize(m + 1);

    for (int i = 1; i <= m; i++) {
        min_v[i] = min_v[i - 1] + i * i * i;
        min_s[i] = min_s[i - 1] + 2 * i * i;
    }
}

void dfs(int d, int v, int s) {
    if (d == 0) {
        if (v == n) { ans = min(ans, s); }
        return;
    }
    if (v + min_v[d] > n) { return; }
    if (s + min_s[d] >= ans) { return; }
    r[d] = min(r[d + 1] - 1, int(sqrt((n - v) / d)));
    for (; r[d] >= d; r[d]--) {
        h[d] = min(h[d + 1] - 1, (n - v) / (r[d] * r[d]));
        for (; h[d] >= d; h[d]--) {
            int nv = v + r[d] * r[d] * h[d];
            int ns = s + 2 * r[d] * h[d];
            if (d == m) { ns += r[d] * r[d]; }
            if (2 * (n - v) / r[d] + s < ans) {
                dfs(d - 1, nv, ns);
            }
        }
    }
}

void solve() {
    dfs(m, 0, 0);
    if (ans == 0x3f3f3f3f) { ans = 0; }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("1.in", "r", stdin);

    cin >> n >> m;

    init();
    solve();
}