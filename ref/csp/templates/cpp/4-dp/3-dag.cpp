// DAG上的DP
//
// 洛谷 UVA437: The Tower of Babylon
//
// example:
//
// input:
// 1
// 10 20 30
// 2
// 6 8 10
// 5 5 5
// 7
// 1 1 1
// 2 2 2
// 3 3 3
// 4 4 4
// 5 5 5
// 6 6 6
// 7 7 7
// 5
// 31 41 59
// 26 53 58
// 97 93 23
// 84 62 64
// 33 83 27
// 0
//
// output:
// Case 1: maximum height = 40
// Case 2: maximum height = 21
// Case 3: maximum height = 28
// Case 4: maximum height = 342

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

using ll = long long;
using tri = tuple<int, int, int>;

int inf = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<tri> blocks;
    vector<int> block(3);

    auto f = [&]() {
        vector<tri> vs;
        for (auto [x, y, z] : blocks) {
            vs.push_back({x, y, z});
            vs.push_back({x, z, y});
            vs.push_back({y, z, x});
        }

        tri ground = {inf, inf, 0};
        vs.push_back(ground);

        sort(vs.begin(), vs.end());
        vs.erase(unique(vs.begin(), vs.end()), vs.end());

        unordered_map<int, unordered_map<int, int>> g;
        unordered_map<int, int> indeg;

        for (int i = 0; i < vs.size(); i++) {
            for (int j = 0; j < vs.size(); j++) {
                if (i == j) {
                    continue;
                }
                tri u = vs[i];
                tri v = vs[j];
                if (get<0>(u) > get<0>(v) && get<1>(u) > get<1>(v)) {
                    g[i][j] = get<2>(v);
                    indeg[j]++;
                }
            }
        }

        queue<int> q;
        q.push(vs.size() - 1);

        vector<int> topo;

        while (!q.empty()) {
            int i = q.front();
            q.pop();

            topo.push_back(i);

            for (auto [j, w] : g[i]) {
                indeg[j]--;
                if (indeg[j] == 0) {
                    q.push(j);
                }
            }
        }

        unordered_map<int, int> dp;

        for (auto i : topo) {
            for (auto [j, w] : g[i]) {
                dp[j] = max(dp[j], dp[i] + w);
            }
        }

        int ans = 0;
        for (auto [k, v] : dp) {
            ans = max(ans, v);
        }
        return ans;
    };

    vector<int> res;
    int n;
    while (cin >> n) {
        if (n == 0) {
            break;
        }
        for (int i = 1; i <= n; i++) {
            cin >> block[0] >> block[1] >> block[2];
            sort(block.begin(), block.end());
            blocks.push_back({block[0], block[1], block[2]});
        }
        res.push_back(f());
        blocks.clear();
    }

    for (int i = 0; i < res.size(); i++) {
        cout << "Case " << i + 1 << ": maximum height = " << res[i] << endl;
    }
}
