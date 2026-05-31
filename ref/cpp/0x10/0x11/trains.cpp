#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    static stack<int> s;
    static vector<int> v;

    int cnt = 0;

    auto dfs = [&](auto &&self, int pos) -> void {
        if (cnt >= 20) {
            return;
        }

        if (v.size() >= n) {
            for (const auto &x : v) {
                cout << x;
            }
            cout << endl;
            cnt++;
            return;
        }

        if (!s.empty() && v.size() < n) {
            v.push_back(s.top());
            s.pop();
            self(self, pos);
            s.push(v.back());
            v.pop_back();
        }

        if (pos <= n) {
            s.push(pos);
            self(self, pos + 1);
            s.pop();
        }
    };

    dfs(dfs, 1);
}