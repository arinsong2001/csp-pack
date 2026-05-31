#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int a, b, p;

ll modexp_recurrence(int x, int y, int m) {
    ll ans = 1 % m;
    ll tmp = x % m;

    for (int i = 0; y >> i; i++) {
        if (y >> i & 1) ans = ans * tmp % m;
        tmp = tmp * tmp % m;
    }

    return ans;
}

ll modexp_recursion(int x, int y, int m) {
    if (!y) return 1 % m;

    ll ans = modexp_recursion((ll)x * x % m, y >> 1, m);
    if (y & 1) ans = ans * x % m;

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("1.in", "r", stdin);

    cin >> a >> b >> p;

    cout << modexp_recursion(a, b, p) << endl;
}