#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int n;

bool is_prime(int x) {
    assert(x > 1);
    if (x == 2) {
        return true;
    }
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 2; i <= n; i++) {
        if (!is_prime(i)) {
            continue;
        }
        ll t = i;
        int c = 0;
        while (t <= n) {
            c += n / t;
            t *= i;
        }
        cout << i << ' ' << c << '\n';
    }
}