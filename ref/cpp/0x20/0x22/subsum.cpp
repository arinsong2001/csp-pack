#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using cd = complex<double>;

vector<int> stov(const string &s) {
    return s | views::reverse | views::transform([](const auto &x) {
        return x - '0';
    }) | ranges::to<vector<int>>();
}

string vtos(const vector<int> &v) {
    return v | views::reverse | views::transform([](const auto &x) {
        return '0' + x;
    }) | ranges::to<string>();
}

void trim(vector<int> &v) {
    while (v.size() > 1 && v.back() == 0) {
        v.pop_back();
    }
}

void fft(vector<cd> &arr, bool inv) {
    int n = arr.size();
    if (n == 1) {
        return;
    }

    auto even = vector<cd>(n >> 1);
    auto odd = vector<cd>(n >> 1);
    for (int i = 0; i < n >> 1; i++) {
        even[i] = arr[i << 1];
        odd[i] = arr[(i << 1) + 1];
    }

    fft(even, inv);
    fft(odd, inv);

    auto ang = 2 * numbers::pi / n * (inv ? -1 : 1);
    auto wn = cd(cos(ang), sin(ang));
    auto wi = cd(1);
    for (int k = 0; k < n >> 1; k++) {
        auto u = even[k];
        auto v = wi * odd[k];
        arr[k] = u + v;
        arr[k + (n >> 1)] = u - v;
        wi *= wn;
    }
}

vector<int> mul(const vector<int> &x, const vector<int> &y) {
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

auto s = vector<int>{};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    while (cin >> t) {
        s.push_back(t);
    }

    // ll ans = (ll)accumulate(s.begin(), s.end(), 0) << (s.size() - 1);
    // cout << ans << endl;

    ll x = accumulate(s.begin(), s.end(), 0);
    auto sx = format("{}", x);
    auto vx = stov(sx);

    ll y = 1 << (s.size() - 1);
    auto sy = format("{}", y);
    auto vy = stov(sy);

    auto res = mul(vx, vy);
    auto ans = vtos(res);

    cout << ans << endl;
}