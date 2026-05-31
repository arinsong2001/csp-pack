#include <bits/stdc++.h>

using namespace std;

int n, m;

auto arr = vector<int>{};
auto diff = vector<int>{};

auto c = vector<int>{};

void build(const vector<int> &a) {
    c.insert(c.end(), a.begin(), a.end());
    for (int i = 1; i <= n; i++) {
        int j = i + (i & -i);
        if (j <= n) { c[j] += c[i]; }
    }
}

int ask(int i) {
    int ans = 0;
    for (; i; i -= i & -i) { ans += c[i]; }
    return ans;
}

void add(int i, int v) {
    for (; i <= n; i += i & -i) { c[i] += v; }
}

void operate(int l, int r, int v) {
    add(l, v);
    if (r + 1 <= n) { add(r + 1, -v); }
}

void init() {
    arr.resize(n + 1);
    for (int i = 1; i <= n; i++) { cin >> arr[i]; }

    diff.resize(n + 1);
    adjacent_difference(arr.begin(), arr.end(), diff.begin());

    build(diff);
}

void solve() {
    for (int i = 0; i < m; i++) {
        char c;
        cin >> c;
        if (c == 'C') {
            int l, r, d;
            cin >> l >> r >> d;
            operate(l, r, d);
        } else if (c == 'Q') {
            int x;
            cin >> x;
            cout << ask(x) << '\n';
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