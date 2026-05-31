#include <bits/stdc++.h>

using namespace std;

int n;
set<pair<int, int>> s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    int a;
    cin >> a;
    s.insert({a, 1});

    auto show = [&](int a, auto it) {
        cout << abs(a - it->first) << ' ' << it->second << endl;
    };

    for (int i = 2; i <= n; i++) {
        cin >> a;
        auto b = s.lower_bound({a, i});
        if (b == s.begin()) {
            show(a, b);
        } else {
            auto f = prev(b);
            if (b == s.end()) {
                show(a, f);
            } else {
                auto diff_f = abs(a - f->first);
                auto diff_b = abs(a - b->first);
                if (diff_f <= diff_b) {
                    show(a, f);
                } else {
                    show(a, b);
                }
            }
        }
        s.insert({a, i});
    }
}