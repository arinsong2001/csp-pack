#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using cd = complex<double>;

const double PI = acos(-1);

void type(auto &&arg) {
    cout << __PRETTY_FUNCTION__ << endl;
}

void show(const auto &r) {
    ranges::for_each(r, [&](const auto &x) { cout << x << ' '; });
    cout << endl;
}

vector<int> stov(const string &s) {
    auto v = vector<int>{};
    for (int i = s.size() - 1; i >= 0; i--) {
        v.push_back(s[i] - '0');
    }
    return v;
}

string vtos(const vector<int> &v) {
    auto s = string{};
    for (int i = v.size() - 1; i >= 0; i--) {
        s += '0' + v[i];
    }
    return s;
}

void trim(vector<int> &v) {
    while (v.size() > 1 && !v.back()) {
        v.pop_back();
    }
}

void fft(vector<cd> &arr, bool inv) {
    int n = arr.size();
    if (n == 1) {
        return;
    }

    // divide arr into even & odd
    auto even = vector<cd>(n >> 1);
    auto odd = vector<cd>(n >> 1);
    for (int i = 0; i << 1 < n; i++) {
        even[i] = arr[i << 1];
        odd[i] = arr[(i << 1) + 1];
    }

    // recursion
    fft(even, inv);
    fft(odd, inv);

    // butterfly
    auto ang = 2 * PI / n * (inv ? -1 : 1);
    auto wn = cd(cos(ang), sin(ang));
    auto wi = cd(cos(0), sin(0));
    for (int k = 0; k << 1 < n; k++) {
        auto u = even[k];
        auto v = wi * odd[k];
        arr[k] = u + v;
        arr[k + (n >> 1)] = u - v;
        wi *= wn;
    }
}

vector<int> mul4(const vector<int> &x, const vector<int> &y) {
    auto cx = vector<cd>(x.begin(), x.end());
    auto cy = vector<cd>(y.begin(), y.end());

    int n = 1;
    while (n < x.size() + y.size()) {
        n <<= 1;
    }
    cx.resize(n);
    cy.resize(n);

    fft(cx, false);
    fft(cy, false);

    for (int i = 0; i < n; i++) {
        cx[i] *= cy[i];
    }

    fft(cx, true);

    auto res = vector<int>(n);
    for (int i = 0; i < n; i++) {
        res[i] = round(cx[i].real() / n);
    }

    ll tmp = 0;
    for (int i = 0; i < n; i++) {
        tmp += res[i];
        res[i] = tmp % 10;
        tmp /= 10;
    }

    trim(res);

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1 = "123";
    string s2 = "45";

    auto v1 = stov(s1);
    auto v2 = stov(s2);

    auto v_mul4 = mul4(v1, v2);
    assert(vtos(v_mul4) == "5535");
}