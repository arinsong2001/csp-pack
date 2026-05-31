#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    static vector<int> res;

    auto choice = [&](auto &&self, int pos) {
        if (res.size() > m || res.size() + n - pos + 1 < m) {
            return;
        }
        if (pos > n) {
            for (int i = 0; i < res.size(); i++) {
                cout << res[i] << " ";
            }
            cout << '\n';
            return;
        }
        res.push_back(pos);
        self(self, pos + 1);
        res.pop_back();
        self(self, pos + 1);
    };

    choice(choice, 1);
}