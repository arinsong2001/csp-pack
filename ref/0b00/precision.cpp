#include <bits/stdc++.h>

using namespace std;

using ll = long long;

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

vector<int> add(const vector<int> &x, const vector<int> &y) {
    int tmp = 0;
    vector<int> res;
    int i = 0;
    for (int i = 0; i < x.size() || i < y.size(); i++) {
        if (i < x.size()) {
            tmp += x[i];
        }
        if (i < y.size()) {
            tmp += y[i];
        }
        res.push_back(tmp % 10);
        tmp /= 10;
    }
    while (tmp) {
        res.push_back(tmp % 10);
        tmp /= 10;
    }
    return res;
}

vector<int> sub(const vector<int> &x, const vector<int> &y) {
    assert(x.size() > y.size() || x.size() == y.size() && x >= y);
    int tmp = 0;
    vector<int> res;
    for (int i = 0; i < x.size(); i++) {
        tmp = x[i] - tmp;
        if (i < y.size()) {
            tmp -= y[i];
        }
        res.push_back((tmp + 10) % 10);
        tmp = tmp < 0;
    }
    while (res.size() > 1 && res.back() == 0) {
        res.pop_back();
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
    reverse(q.begin(), q.end());
    while (q.size() > 1 && q.back() == 0) {
        q.pop_back();
    }
    return {q, r};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1 = "12345";
    string s2 = "23456";
    int num = 5;

    auto v1 = stov(s1);
    auto v2 = stov(s2);

    // clang only!
    // cout << format("{}", v) << endl;

    auto sum = add(v1, v2);
    cout << format("sum of v1 and v2 is: {}", vtos(sum)) << endl;

    auto diff = sub(v2, v1);
    cout << format("diff of v2 and v1 is: {}", vtos(diff)) << endl;

    auto prod = mul(v1, num);
    cout << format("prod of v1 and num is: {}", vtos(prod)) << endl;

    auto [q, r] = divmod(v1, num);
    cout << format("q and r from divmod(v1, num) are: [{}, {}]", vtos(q), r) << endl;
}
