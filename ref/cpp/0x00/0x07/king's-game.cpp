#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct M {
    int l, r;
    bool operator<(const M &other) const {
        return l * r < other.l * other.r;
    }
};

vector<int> stov(const string &s) {
    vector<int> res;
    res.reserve(s.size());
    for (int i = s.size() - 1; i >= 0; i--) {
        res.push_back(s[i] - '0');
    }
    return res;
}

string vtos(const vector<int> &v) {
    string res;
    for (int i = v.size() - 1; i >= 0; i--) {
        res += '0' + v[i];
    }
    return res;
}

vector<int> mul(const vector<int> &x, int y) {
    if (y == 0) {
        return {0};
    }
    assert(y > 0);
    ll tmp = 0;
    vector<int> res;
    for (int i = 0; i < x.size(); i++) {
        tmp += ll(x[i]) * y;
        res.push_back(tmp % 10);
        tmp /= 10;
    }
    while (tmp) {
        res.push_back(tmp % 10);
        tmp /= 10;
    }
    return res;
}

pair<vector<int>, int> divmod(const vector<int> &x, int y) {
    assert(y > 0);
    ll r = 0;
    vector<int> q;
    for (int i = x.size() - 1; i >= 0; i--) {
        r = r * 10 + x[i];
        q.push_back(r / y);
        r %= y;
    }
    // ranges::reverse(q);
    reverse(q.begin(), q.end());
    while (q.size() > 1 && q.back() == 0) {
        q.pop_back();
    }
    return {q, r};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    static M ms[1010];

    cin >> ms[0].l >> ms[0].r;

    for (int i = 1; i <= n; i++) {
        cin >> ms[i].l >> ms[i].r;
    }

    sort(ms + 1, ms + n + 1);

    // arbitrary precision

    // auto s = format("{}", ms[0].l);
    char buf[30];
    snprintf(buf, sizeof(buf), "%d", ms[0].l);
    string s(buf);

    static vector<vector<int>> prod{stov(s)};

    for (int i = 1; i < n; i++) {
        prod.push_back(mul(prod.back(), ms[i].l));
    }

    string ans;
    for (int i = 1; i <= n; i++) {
        auto [q, r] = divmod(prod[i - 1], ms[i].r);
        auto s = vtos(q);
        if (s.size() > ans.size() || s.size() == ans.size() && s > ans) {
            ans = s;
        }
    }

    cout << ans << endl;
}