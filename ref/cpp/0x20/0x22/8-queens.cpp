#include <bits/stdc++.h>

using namespace std;

int n, m;

auto bs = vector<int>{};

auto as = vector<vector<int>>{};
auto a = vector<int>{};

int all;

void dfs(int row, int col, int main_d, int anti_d) {
    if (col == all) {
        as.push_back(a);
        return;
    }
    for (auto alts = all & ~(col | main_d | anti_d); alts; alts &= alts - 1) {
        int lb = alts & -alts;
        auto pos = lb ? __builtin_ctz(unsigned(lb)) : 0;
        pos = n - pos;
        a.push_back(pos);
        dfs(row + 1, col + lb, (main_d + lb) >> 1, (anti_d + lb) << 1);
        a.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    n = 8;
    cin >> m;

    bs.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> bs[i];
    }

    all = (1 << n) - 1;
    dfs(0, 0, 0, 0);

    sort(as.begin(), as.end());

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << as[bs[i] - 1][j];
        }
        cout << '\n';
    }
}