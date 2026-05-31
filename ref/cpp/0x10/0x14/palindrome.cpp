#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

string s;
int id = 1;

ull p[1000010];
ull f[1000010];
ull b[1000010];

ull get_hash(int l, int r, ull pref[]) {
    return l - 1 >= 0 ? pref[r] - pref[l - 1] * p[r - l + 1] : pref[r];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    p[0] = 1;
    for (int i = 1; i < 1000010; i++) {
        p[i] = p[i - 1] * 131;
    }

    // odd:
    // i to i + ∆
    // i to i - ∆
    //
    // x -> 0 + sz - x-> sz - x
    // sz - 1 - i to sz - 1 - (i - ∆)
    //
    // fh = get_hash(i + 1, i + ∆, f)
    // bh = get_hash(sz - 1 - i, sz - 1 - (i - ∆), b)
    //
    // ∆ = 0
    // while i - ∆ >= 0 && i + ∆ < sz:
    //   fh != bh -> break
    //   ∆++
    //
    // len_odd = 2 * ∆ + 1
    //
    // even:
    // i + 1 to i + 1 + ∆
    // i to i - ∆
    // sz - 1 - i to sz - 1 - (i - ∆)
    //
    // fh = get_hash(i + 1, i + 1 + ∆, f)
    // bh = get_hash(sz - 1 - i, sz - 1 - (i - ∆), b)
    //
    // len_even = 2 * ∆ + 2
    //
    // ∆ = 0
    // while i - ∆ >= 0 && i + 1 + ∆ < sz:
    //   fh != bh -> break
    //   ∆++

    auto check_odd = [&](int i, int delta, int sz) {
        if (i - delta < 0 || i + delta >= sz) {
            return false;
        }
        auto fh = get_hash(i, i + delta, f);
        auto bh = get_hash(sz - 1 - i, sz - 1 - (i - delta), b);
        return fh == bh;
    };

    auto check_even = [&](int i, int delta, int sz) {
        if (i - delta < 0 || i + 1 + delta >= sz) {
            return false;
        }
        auto fh = get_hash(i + 1, i + 1 + delta, f);
        auto bh = get_hash(sz - 1 - i, sz - 1 - (i - delta), b);
        return fh == bh;
    };

    int id = 1;
    while (cin >> s && s != "END") {
        int sz = s.size();
        if (!sz) {
            cout << "Case " << id++ << ": " << 0 << '\n';
            continue;
        }
        f[0] = s[0];
        for (int i = 1; i < sz; i++) {
            f[i] = f[i - 1] * 131 + s[i];
        }
        b[0] = s[sz - 1];
        for (int i = 1; i < sz; i++) {
            b[i] = b[i - 1] * 131 + s[sz - 1 - i];
        }

        int ans = 0;
        for (int i = 0; i < sz; i++) {
            int delta, step;

            // for (delta = 0; i - delta >= 0 && i + delta < sz; delta++) {
            //     auto fh = get_hash(i, i + delta, f);
            //     auto bh = get_hash(sz - 1 - i, sz - 1 - (i - delta), b);
            //     if (fh != bh) {
            //         break;
            //     }
            // }
            // ans = max(ans, (delta - 1) * 2 + 1);

            delta = 0, step = 1;
            while (step) {
                if (check_odd(i, delta + step, sz)) {
                    delta += step;
                    step <<= 1;
                } else {
                    step >>= 1;
                }
            }

            ans = max(ans, delta * 2 + 1);

            // for (delta = 0; i - delta >= 0 && i + 1 + delta < sz; delta++) {
            //     auto fh = get_hash(i + 1, i + 1 + delta, f);
            //     auto bh = get_hash(sz - i - 1, sz - 1 - (i - delta), b);
            //     if (fh != bh) {
            //         break;
            //     }
            // }
            // ans = max(ans, (delta - 1) * 2 + 2);

            delta = -1, step = 1;

            while (step) {
                if (check_even(i, delta + step, sz)) {
                    delta += step;
                    step <<= 1;
                } else {
                    step >>= 1;
                }
            }

            ans = max(ans, delta * 2 + 2);
        }

        cout << "Case " << id++ << ": " << ans << '\n';
    }
}