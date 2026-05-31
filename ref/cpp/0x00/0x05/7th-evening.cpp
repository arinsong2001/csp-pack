#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // x // 2 <= (x + 1) // 2 <= x // 2 + 1
    // 0-based(lower), 1-based(lower) or 0-based(upper), 1-based(upper)
    // (l + r) // 2 -> lower: (x + 1) // 2 <=> (0 + x + 1) // 2 -> 0-based(upper)
    // (l + r + 1) // 2 -> upper: x // 2 + 1 <=> (1 + x + 1) // 2 -> 1-based(upper)

    ll N, M, T;
    cin >> N >> M >> T;

    // row[i] -> ith row's cnt of points
    // col[i] -> ith col's cnt of points
    vector<ll> row(N + 1);
    vector<ll> col(M + 1);
    for (ll i = 0; i < T; i++) {
        ll x, y;
        cin >> x >> y;
        row[x]++, col[y]++;
    }

    string status;
    if (!(T % N) && !(T % M)) {
        status = "both";
    } else if (!(T % N)) {
        status = "row";
    } else if (!(T % M)) {
        status = "column";
    } else {
        status = "impossible";
    }

    auto adjust_row = [&](vector<ll> row) -> ll {
        ll base = T / N;
        for (auto &x : row) {
            x -= base;
        }
        partial_sum(row.begin() + 1, row.end(), row.begin() + 1);
        sort(row.begin() + 1, row.end());
        ll idx = (1 + N) >> 1;
        ll pos = row[idx];
        ll ans = 0;
        for (ll i = 1; i <= N; i++) {
            ans += abs(pos - row[i]);
        }
        return ans;
    };

    auto adjust_col = [&](vector<ll> col) -> ll {
        ll base = T / M;
        for (auto &x : col) {
            x -= base;
        }
        partial_sum(col.begin() + 1, col.end(), col.begin() + 1);
        sort(col.begin() + 1, col.end());
        ll idx = (1 + M) >> 1;
        ll pos = col[idx];
        ll ans = 0;
        for (ll i = 1; i <= M; i++) {
            ans += abs(pos - col[i]);
        }
        return ans;
    };

    if (status == "both") {
        cout << status << ' ' << adjust_row(row) + adjust_col(col) << endl;
    } else if (status == "row") {
        cout << status << ' ' << adjust_row(row) << endl;
    } else if (status == "column") {
        cout << status << ' ' << adjust_col(col) << endl;
    } else {
        cout << status << endl;
    }
}