#include <bits/stdc++.h>

using namespace std;

void type(auto &&...args) {
    cout << __PRETTY_FUNCTION__ << endl;
}

void echo(auto &&...args) {
    ((cout << format("{} ", args)), ...);
    cout << endl;
}

int n;

auto board = vector<int>{};

int cnt = 0;

int all;

void dfs(int row, int col, int main_d, int anti_d) {
    if (col == all) {
        cnt++;
        return;
    }
    int alts = all & ~(board[row] | col | main_d | anti_d);
    while (alts) {
        int lb = alts & -alts;
        alts &= alts - 1;
        dfs(row + 1, col + lb, (main_d + lb) >> 1, (anti_d + lb) << 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("1.in", "r", stdin);

    cin >> n;

    board.resize(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == '.') {
                board[i] |= 1 << (n - 1 - j);
            }
        }
    }

    all = (1 << n) - 1;
    dfs(0, 0, 0, 0);

    cout << cnt << endl;
}