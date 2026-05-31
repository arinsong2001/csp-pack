#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int n, m, q, u, v, t;

deque<ll> xq, pq, rq;
ll delta = 0;

vector<ll> sliced;

vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q >> u >> v >> t;

    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a.begin() + 1, a.end(), greater<>());

    for (int i = 1; i <= n; i++) {
        xq.push_back(a[i]);
    }

    auto exec = [&](ll x) {
        x += delta;
        sliced.push_back(x);

        ll f = x * u / v;
        ll b = x - f;

        f = f - delta - q;
        b = b - delta - q;

        pq.push_back(f);
        rq.push_back(b);
    };

    for (int i = 1; i <= m; i++) {
        ll x = xq.empty() ? numeric_limits<ll>::min() : xq.front();
        ll px = pq.empty() ? numeric_limits<ll>::min() : pq.front();
        ll rx = rq.empty() ? numeric_limits<ll>::min() : rq.front();

        ll max_val = max({x, px, rx});

        if (max_val == x) {
            xq.pop_front();
            exec(x);
        } else if (max_val == px) {
            pq.pop_front();
            exec(px);
        } else if (max_val == rx) {
            rq.pop_front();
            exec(rx);
        } else {
            throw runtime_error("wrong max_val!");
        }

        delta += q;
    }

    for (int i = t; i <= sliced.size(); i += t) {
        cout << sliced[i - 1] << ' ';
    }
    cout << endl;

    vector<ll> res;
    for (auto x : xq) {
        res.push_back(x + delta);
    }
    for (auto x : pq) {
        res.push_back(x + delta);
    }
    for (auto x : rq) {
        res.push_back(x + delta);
    }

    sort(res.begin(), res.end(), greater<>());

    for (int i = t; i <= res.size(); i += t) {
        cout << res[i - 1] << ' ';
    }
    cout << endl;
}