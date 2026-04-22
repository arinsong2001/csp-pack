#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

int bit_len(ull x) {
    return !x ? 0 : 64 - __builtin_clz(x);
}

int lb(int x) {
    return x & -x;
}

int hb(int x) {
    return !x ? 0 : bit_len(x) - 1;
}

int randint(int l, int r) {
    auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    return l + rng() % (r - l + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = randint(1, 1000);

    assert((n & n - 1) == n - lb(n));        // reset lb
    assert((n ^ n - 1) == (lb(n) << 1) - 1); // generate a mask led by lb
    assert((n | n - 1) == n + lb(n) - 1);    // set trailing zeros
    assert((n | n - 1) + 1 == n + lb(n));

    assert(~n != 0);
    int pos = __builtin_ctz(~n);

    assert((n & n + 1) == (n & ~((1 << pos) - 1))); // reset trailing ones
    assert((n ^ n + 1) == (1 << (pos + 1)) - 1);    // generate a mask led by lb0
    assert((n | n + 1) == (n | 1 << pos));          // set lb0

    int mask = n, cnt = 0;

    for (int x = mask; x; x = x - 1 & mask, cnt++);
    assert(cnt + 1 == 1 << __builtin_popcount(mask));
}
