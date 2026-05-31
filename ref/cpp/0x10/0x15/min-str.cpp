#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    getline(cin, s, '\n');
    s = s | views::filter([&](const auto &x) { return x != ' '; }) | ranges::to<string>();

    auto min_str = [&](string s) {
        string t = s + s;
        int i = 0, j = 1;
        while (i < s.size() && j < s.size()) {
            int k = 0;
            for (; k < s.size() && t[i + k] == t[j + k]; k++);
            if (k == s.size()) {
                return t.substr(min(i, j), s.size());
            }
            if (t[i + k] < t[j + k]) {
                j += k + 1;
                if (i == j) {
                    j++;
                }
            } else {
                i += k + 1;
                if (i == j) {
                    i++;
                }
            }
        }
        return t.substr(min(i, j), s.size());
    };

    cout << min_str(s) << endl;
}