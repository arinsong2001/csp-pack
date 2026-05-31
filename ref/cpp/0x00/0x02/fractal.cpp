#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // n queries
    int n;
    cin >> n;

    // N -> x, y : [0, 2**N - 1] -> len = 2**(N - 1)

    auto calc = [&](auto &&self, int N, ll M) -> complex<ll> {
        if (N == 0) {
            return {0, 0};
        }

        ll len = 1ll << (N - 1);
        ll cnt = 1ll << (2 * N - 2);

        // M // cnt : 0, 1, 2, 3
        // M % cnt

        auto c = self(self, N - 1, M % cnt);
        auto i = c.real(), j = c.imag();

        auto quot = M / cnt;

        switch (quot) {
        case 0:
            return complex{j, i};
        case 1:
            return complex{i, j + len};
        case 2:
            return complex{i + len, j + len};
        case 3:
            return complex{2 * len - 1 - j, len - 1 - i};
        default:
            throw runtime_error("error!");
        }
    };

    for (int i = 0; i < n; i++) {
        int N;
        ll A, B;
        cin >> N >> A >> B;
        auto c1 = calc(calc, N, A - 1);
        complex<double> cd1(c1.real(), c1.imag());
        auto c2 = calc(calc, N, B - 1);
        complex<double> cd2(c2.real(), c2.imag());
        auto ans = (ll)round(10 * abs(cd1 - cd2));
        cout << ans << '\n';
    }
}