#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int mod = 9901;

int a, b;

const int M = 1e4;
int p[M], c[M];

int divide(int n) {
    int m = 0;
    for (int i = 2; i <= (int)sqrt(n); i++) {
        if (n % i == 0) {
            p[++m] = i;
            c[m] = 0;
            while (n % i == 0) {
                n /= i;
                c[m]++;
            }
        }
    }
    if (n > 1) {
        p[++m] = n;
        c[m] = 1;
    }
    return m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;

    if (a == 0) {
        cout << 0 << endl;
        return 0;
    }
    if (b == 0) {
        cout << 1 << endl;
        return 0;
    }

    int m = divide(a);

    // ranges::for_each(span(p + 1, m), [&](auto x) { cout << x << ' '; });
    // cout << endl;
    // ranges::for_each(span(c + 1, m), [&](auto x) { cout << x << ' '; });
    // cout << endl;

    ll prod = 1;

    auto pow = [&](auto &&self, ll x, ll p) -> ll {
        if (p == 0) {
            return 1;
        }
        auto t = self(self, x * x % mod, p >> 1);
        return p & 1 ? t * x % mod : t;
    };

    // cout << pow(pow, 3, 5) << endl;

    auto sum = [&](auto &&self, ll p, ll c) -> ll {
        if (!c) {
            return 1;
        }
        if (c & 1) {
            return (1 + pow(pow, p, (c + 1) >> 1)) % mod * self(self, p, (c - 1) >> 1) % mod;
        } else {
            return ((1 + pow(pow, p, c >> 1)) % mod * self(self, p, (c >> 1) - 1) % mod + pow(pow, p, c)) % mod;
        }
    };

    for (int i = 1; i <= m; i++) {
        prod = prod * sum(sum, p[i], (ll)c[i] * b) % mod;
    }
    cout << prod << endl;
}