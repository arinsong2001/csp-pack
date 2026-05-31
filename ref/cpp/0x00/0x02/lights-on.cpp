#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    static const int M = 5;

    static vector<vector<vector<int>>> groups;
    static vector<vector<int>> tmp(M, vector<int>(M));

    for (int i = 0; i < n; i++) {
        for (int i = 0; i < M; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < M; j++) {
                tmp[i][j] = s[j] - '0';
            }
        }
        groups.push_back(tmp);
    }

    auto press = [&](vector<vector<int>> &lights, int i, int j) {
        auto prs = [&](const auto &...args) {
            auto pr = [&](const auto &p) {
                if (0 <= p.first && p.first < lights.size() && 0 <= p.second && p.second < lights[0].size()) {
                    lights[p.first][p.second] ^= 1;
                }
            };
            (pr(args), ...);
        };
        prs(pair{i, j}, pair{i - 1, j}, pair{i + 1, j}, pair{i, j - 1}, pair{i, j + 1});
    };

    for (const auto &ls : groups) {
        int ans = 0x3f3f3f3f;
        for (int i = 0; i < 1 << M; i++) {
            auto lights(ls);
            int cnt = 0;

            bitset<M> b(i);
            for (int j = 0; j < M; j++) {
                if (b[j]) {
                    press(lights, 0, j);
                    cnt++;
                }
            }
            for (int k = 1; k < M; k++) {
                for (int l = 0; l < M; l++) {
                    if (!lights[k - 1][l]) {
                        press(lights, k, l);
                        cnt++;
                    }
                }
            }
            if (any_of(lights[M - 1].begin(), lights[M - 1].end(), [](int x) {
                    return !x;
                })) {
                cnt = 0x3f3f3f3f;
            }
            ans = min(ans, cnt);
        }
        cout << (ans > 6 ? -1 : ans) << '\n';
    }
}