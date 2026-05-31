#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> res;
    vector<int> path;

    auto f = [&](auto &&self, int pos, int rsrc, int prev) -> void {
        if (pos > m) {
            if (rsrc == 0) {
                res.push_back(path);
            }
            return;
        }

        for (int x = prev + 1; rsrc - x >= 0; x++) {
            int k = m - pos;
            int min_sum = k * (2 * x + k + 1) / 2;

            if (rsrc - x - min_sum < 0) {
                break;
            }

            path.push_back(x);
            self(self, pos + 1, rsrc - x, x);
            path.pop_back();
        }
    };

    f(f, 1, n, 0);

    for (auto p : res) {
        for (auto x : p) {
            cout << x << " ";
        }
        cout << "\n";
    }
}
