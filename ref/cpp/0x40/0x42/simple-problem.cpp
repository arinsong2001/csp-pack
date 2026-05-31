#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll n, m;

auto arr = vector<ll>{};

auto diff = vector<ll>{};
auto i_diff = vector<ll>{};

auto c = vector<ll>{};
auto i_c = vector<ll>{};

void build(const vector<ll> &a, vector<ll> &c) {
    c.insert(c.end(), a.begin(), a.end());
    for (ll i = 1; i <= n; i++) {
        ll j = i + (i & -i);
        if (j <= n) { c[j] += c[i]; }
    }
}

ll ask(ll i, const vector<ll> &c) {
    ll ans = 0;
    for (; i; i -= i & -i) { ans += c[i]; }
    return ans;
}

ll query(ll l, ll r) {
    auto calc = [&](ll x) { return (x + 1) * ask(x, c) - ask(x, i_c); };
    return calc(r) - calc(l - 1);
}

void add(ll i, ll v, vector<ll> &c) {
    for (; i <= n; i += i & -i) { c[i] += v; }
}

void operate(ll l, ll r, ll v, vector<ll> &c) {
    add(l, v, c);
    if (r + 1 <= n) { add(r + 1, -v, c); }
}

void i_operate(ll l, ll r, ll v, vector<ll> &c) {
    add(l, l * v, c);
    if (r + 1 <= n) { add(r + 1, -(r + 1) * v, c); }
}

void init() {
    arr.resize(n + 1);
    for (ll i = 1; i <= n; i++) { cin >> arr[i]; }

    diff.resize(n + 1);
    adjacent_difference(arr.begin(), arr.end(), diff.begin());

    i_diff.insert(i_diff.end(), diff.begin(), diff.end());
    for (ll i = 1; i <= n; i++) { i_diff[i] *= i; }

    build(diff, c);
    build(i_diff, i_c);
}

void solve() {
    for (ll i = 0; i < m; i++) {
        char cmd;
        cin >> cmd;
        if (cmd == 'C') {
            ll l, r, d;
            cin >> l >> r >> d;
            operate(l, r, d, c);
            i_operate(l, r, d, i_c);
        } else if (cmd == 'Q') {
            ll l, r;
            cin >> l >> r;
            cout << query(l, r) << '\n';
        } else {
            throw runtime_error("wrong c!");
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n >> m;

    init();
    solve();
}