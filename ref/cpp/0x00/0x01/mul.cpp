#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

ll a, b, p;

ll mul(ll x, ll y, ll m) {
    x %= m, y %= m;
    ll ans = 0, tmp = x;
    for (int i = 0; y >> i; i++) {
        if (y >> i & 1) ans = (ans + tmp) % m;
        tmp = (tmp + tmp) % m;
    }
    return ans;
}

ll mul_ld(ll x, ll y, ll m) {
    x %= m, y %= m;
    ull q = (ld)x * y / m;
    auto prod = ll((ull)x * y);
    auto tmp = ll((ull)q * m);
    auto ans = prod - tmp;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("1.in", "r", stdin);

    cin >> a >> b >> p;

    cout << mul_ld(a, b, p) << endl;
}