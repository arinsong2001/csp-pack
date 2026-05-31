#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // int b = (1 << n) - 1;
    // for (; b; b--) {
    //     int t = b;
    //     while (t) {
    //         cout << __builtin_ctz(t) + 1 << " ";
    //         t &= (t - 1);
    //     }
    //     cout << '\n';
    // }
    // cout << endl;

    static vector<int> res;

    auto choice = [&](auto &&self, int pos) {
        if (pos > n) {
            for (int i = 0; i < res.size(); i++) {
                cout << res[i] << " ";
            }
            cout << '\n';
            return;
        }
        self(self, pos + 1);
        res.push_back(pos);
        self(self, pos + 1);
        res.pop_back();
    };

    choice(choice, 1);
}