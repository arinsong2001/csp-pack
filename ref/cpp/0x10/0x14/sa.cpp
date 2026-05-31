#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

string s;

ull f[300010];
ull p[300010];

int length;

inline void prewarm() {
    f[0] = s[0], p[0] = 1;
    for (int i = 1; i < s.size(); i++) {
        f[i] = f[i - 1] * 131 + s[i];
        p[i] = p[i - 1] * 131;
    }
}

inline ull get_hash(int l, int r) {
    return l - 1 >= 0 ? f[r] - f[l - 1] * p[r - l + 1] : f[r];
}

struct Comp {
    bool operator()(int x, int y) const {
        int len = 0, step = 1;

        auto check = [&]() {
            auto rx = x + len - 1 + step;
            auto ry = y + len - 1 + step;
            if (rx >= s.size() || ry >= s.size()) {
                return false;
            }
            return get_hash(x, rx) == get_hash(y, ry);
        };

        // [x, s.size() - 1]
        // [y, s.size() - 1]
        // seek the largest shared prefix length of the two string -> len
        // compare s[x + len] with s[y + len] (at the end -> 0)

        while (step) {
            if (check()) {
                len += step;
                step <<= 1;
            } else {
                step >>= 1;
            }
        }

        auto a = x + len < s.size() ? int(s[x + len]) : 0;
        auto b = y + len < s.size() ? int(s[y + len]) : 0;

        length = len;

        return a < b;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    int len = s.size();

    // auto sf = vector<string>{};
    // for (int i = 0; i < len; i++) {
    //     sf.push_back(s.substr(i, len - i));
    // }

    prewarm();

    auto sa = vector<int>(s.size());
    iota(sa.begin(), sa.end(), 0);

    Comp comp;

    sort(sa.begin(), sa.end(), comp);

    for (auto x : sa) {
        cout << x << ' ';
    }
    cout << endl;

    auto height = vector<int>(s.size());
    height[0] = 0;

    for (int i = 1; i < height.size(); i++) {
        comp(sa[i - 1], sa[i]);
        height[i] = length;
    }

    for (auto x : height) {
        cout << x << ' ';
    }
    cout << endl;
}