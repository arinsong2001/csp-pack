#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mt19937 rng(random_device{}());
    int n = rng() % 1000 + 1;

    auto lb = [&](int x) {
        return x & -x;
    };

    auto hb = [&](int x) {
        return 1 << (31 - __builtin_clz(x));
    };

    assert((n & n - 1) == n - lb(n));     // reset lb
    assert((n ^ n - 1) == 2 * lb(n) - 1); // generate a mask led by lb
    assert((n | n - 1) == n + lb(n) - 1); // set trailing zeros
    assert((n | n - 1) + 1 == n + lb(n));

    assert(~n != 0);

    int pos = __builtin_ctz(~n);
    assert((n & n + 1) == (n & ~((1 << pos) - 1))); // reset trailing ones
    assert((n ^ n + 1) == (1 << (pos + 1)) - 1);    // generate a mask led by lb0
    assert((n | n + 1) == (n | 1 << pos));          // set lb0

    int mask = n;
    int cnt = 0;

    for (int x = mask; x; x = x - 1 & mask) {
        cnt++;
    }
    assert(cnt + 1 == 1 << __builtin_popcount(mask));
}
