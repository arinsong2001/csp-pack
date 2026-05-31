#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    adjacent_difference(a.begin(), a.end(), a.begin());

    ll p = 0, q = 0;

    for (int i = 2; i <= n; i++) {
        if (a[i] > 0) {
            p += a[i];
        } else if (a[i] < 0) {
            q -= a[i];
        }
    }

    ll op_cnt = min(p, q) + abs(p - q);
    ll res_cnt = abs(p - q) + 1;

    cout << op_cnt << '\n'
         << res_cnt << endl;
}