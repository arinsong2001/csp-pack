#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

string s;
int m;

ull f[1000010];
ull p[1000010];

ull get_hash(int l, int r) {
    return l - 1 >= 0 ? f[r] - f[l - 1] * p[r - l + 1] : f[r];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s >> m;
    int sz = s.size();

    p[0] = 1;
    f[0] = p[0] * s[0];

    for (int i = 1; i < sz; i++) {
        f[i] = f[i - 1] * 131 + s[i];
        p[i] = p[i - 1] * 131;
    }

    for (int i = 0; i < m; i++) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        auto former = get_hash(l1 - 1, r1 - 1);
        auto latter = get_hash(l2 - 1, r2 - 1);
        if (former == latter) {
            cout << "Yes" << '\n';
        } else {
            cout << "No" << '\n';
        }
    }
}