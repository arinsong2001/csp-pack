#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void type(auto &&arg) {
    cout << __PRETTY_FUNCTION__ << endl;
}

void show(const auto &r) {
    ranges::for_each(r, [&](const auto &x) { cout << x << ' '; });
    cout << endl;
}

vector<int> stov(const string &s) {
    auto v = vector<int>{};
    for (int i = s.size() - 1; i >= 0; i--)
        v.push_back(s[i] - '0');
    return v;
}

string vtos(const vector<int> &v) {
    auto s = string{};
    for (int i = v.size() - 1; i >= 0; i--)
        s += '0' + v[i];
    return s;
}

void trim(vector<int> &v) {
    while (v.size() > 1 && !v.back()) {
        v.pop_back();
    }
}

vector<int> pls(const vector<int> &x, const vector<int> &y) {
    auto res = vector<int>{};
    ll tmp = 0;
    for (int i = 0; i < x.size() || i < y.size(); i++) {
        if (i < x.size()) tmp += x[i];
        if (i < y.size()) tmp += y[i];
        res.push_back(tmp % 10);
        tmp /= 10;
    }
    while (tmp) {
        res.push_back(tmp % 10);
        tmp /= 10;
    }
    trim(res);
    return res;
}

vector<int> mns(const vector<int> &x, const vector<int> &y) {
    auto ge = [&](const auto &x, const auto &y) {
        if (x.size() != y.size())
            return x.size() > y.size();
        for (int i = x.size() - 1; i >= 0; i--)
            if (x[i] != y[i]) return x[i] > y[i];
        return true;
    };
    assert(ge(x, y));

    auto res = vector<int>{};
    ll tmp = 0;
    for (int i = 0; i < x.size(); i++) {
        tmp = x[i] - tmp;
        if (i < y.size()) tmp -= y[i];
        res.push_back((tmp + 10) % 10);
        if (tmp < 0) tmp = 1;
        else tmp = 0;
    }
    trim(res);
    return res;
}

vector<int> mul(const vector<int> &x, int y) {
    auto res = vector<int>{};
    ll tmp = 0;
    for (int i = 0; i < x.size(); i++) {
        tmp += (ll)x[i] * y;
        res.push_back(tmp % 10);
        tmp /= 10;
    }
    while (tmp) {
        res.push_back(tmp % 10);
        tmp /= 10;
    }
    trim(res);
    return res;
}

vector<int> mul2(const vector<int> &x, const vector<int> &y) {
    auto res = vector<int>(x.size() + y.size());
    ll tmp = 0;
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < y.size(); j++) {
            res[i + j] += x[i] * y[j];
        }
    }
    for (int i = 0; i < res.size(); i++) {
        tmp += res[i];
        res[i] = tmp % 10;
        tmp /= 10;
    }
    trim(res);
    return res;
}

pair<vector<int>, int> divmod(vector<int> x, int y) {
    assert(y > 0);

    auto q = vector<int>{};
    ll r = 0;

    ranges::reverse(x);

    for (int i = 0; i < x.size(); i++) {
        r = r * 10 + x[i];
        q.push_back(r / y);
        r %= y;
    }

    assert(!q.empty());
    auto it = q.begin();
    for (; it != prev(q.end()) && *it == 0; it++);

    q.erase(q.begin(), it);
    ranges::reverse(q);

    return pair{q, r};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1 = "123";
    string s2 = "45";

    auto v1 = stov(s1);
    auto v2 = stov(s2);

    auto v_pls = pls(v1, v2);
    assert(vtos(v_pls) == "168");

    auto v_mns = mns(v1, v2);
    assert(vtos(v_mns) == "78");

    auto v_mul = mul(v1, 45);
    assert(vtos(v_mul) == "5535");

    auto v_mul2 = mul2(v1, v2);
    assert(vtos(v_mul2) == "5535");
}