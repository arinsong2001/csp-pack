#include <bits/stdc++.h>

using namespace std;

string line;

const int N = 9;

auto board = vector<vector<int>>(N, vector<int>(N));
auto row = vector<int>(N);
auto col = vector<int>(N);
auto block = vector<int>(N);

int get_block(int i, int j) {
    return i / 3 * 3 + j / 3;
}

void fill(int i, int j, int num, bool set) {
    board[i][j] = set ? num : 0;
    int bit = 1 << (num - 1);
    row[i] ^= bit;
    col[j] ^= bit;
    block[get_block(i, j)] ^= bit;
}

void init() {
    for (int i = 0; i < N; i++) {
        row[i] = col[i] = block[i] = (1 << N) - 1;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int c = line[N * i + j];
            if (c == '.') {
                board[i][j] = 0;
            } else {
                fill(i, j, c - '0', true);
            }
        }
    }
}

bool dfs() {
    int x, y, min_cnt = 0x3f3f3f3f;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j]) { continue; }
            int mask = row[i] & col[j] & block[get_block(i, j)];
            int cnt = __builtin_popcount(mask);
            if (cnt < min_cnt) {
                x = i, y = j, min_cnt = cnt;
                if (min_cnt == 0) { return false; }
                if (min_cnt == 1) { break; }
            }
        }
        if (min_cnt == 1) { break; }
    }
    if (min_cnt == 0x3f3f3f3f) { return true; }
    int mask = row[x] & col[y] & block[get_block(x, y)];
    for (; mask; mask &= mask - 1) {
        int num = __builtin_ctz(mask) + 1;
        fill(x, y, num, true);
        if (dfs()) { return true; }
        fill(x, y, num, false);
    }
    return false;
}

void solve() {
    auto show = [&]() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << board[i][j];
            }
        }
        cout << '\n';
    };
    if (dfs()) {
        show();
    } else {
        cout << "no solution!" << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("1.in", "r", stdin);

    while (cin >> line && line != "end") {
        init();
        solve();
    }
}