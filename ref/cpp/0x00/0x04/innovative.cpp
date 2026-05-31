#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // e: 1: 2: 3
    // 1: 0, 1, 0
    // 2: 0, 0, 0
    // 3: 1, 1, 0
    //
    // 1 < 2
    // 3 < 1
    // 3 < 2
    //
    // 3, 1, 2

    vector<vector<int>> g;
    g.push_back({0, 1, 0});
    g.push_back({0, 0, 0});
    g.push_back({1, 1, 0});

    auto compare = [&](int a, int b) {
        return bool(g[a - 1][b - 1]);
    };

    // cout << "1 < 2: " << compare(1, 2) << endl;
    // cout << "3 < 1: " << compare(3, 1) << endl;
    // cout << "3 < 2: " << compare(3, 2) << endl;

    auto specialSort = [&](int N) {
        vector<int> res{1};

        for (int i = 2; i <= N; i++) {
            int l = 0, r = res.size();
            while (l < r) {
                int mid = (l + r) >> 1;
                if (compare(res[mid], i)) {
                    l = mid + 1;
                } else {
                    r = mid;
                }
            }
            res.insert(res.begin() + r, i);
        }

        return res;
    };

    auto res = specialSort(3);
    for (auto x : res) {
        cout << x << ' ';
    }
    cout << endl;
}