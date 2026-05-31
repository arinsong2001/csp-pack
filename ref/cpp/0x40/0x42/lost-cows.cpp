#include <bits/stdc++.h>

using namespace std;

int n;

auto a = vector<int>{};
auto b = vector<int>{};
auto c = vector<int>{};
auto h = vector<int>{};

void build(const vector<int> &r) {
    c.insert(c.end(), r.begin(), r.end());
    for (int i = 1; i <= n; i++) {
        int j = i + (i & -i);
        if (j <= n) { c[j] += c[i]; }
    }
}

int query(int i) { return !i ? 0 : c[i] + query(i - (i & -i)); }

bool operate(int i, int v) { return i > n ? true : (c[i] += v, operate(i + (i & -i), v)); }

void init() {
    a.resize(n + 1);
    for (int i = 2; i <= n; i++) { cin >> a[i]; }

    b.resize(n + 1, 1);
    b[0] = 0;

    build(b);

    h.resize(n + 1);
}

int kth(int k) {
    int pos = 0, sum = 0;
    for (int i = 31 - __builtin_clz(n); i >= 0; i--) {
        int nxt = pos + (1 << i);
        if (nxt <= n && sum + c[nxt] < k) { pos = nxt, sum += c[nxt]; }
    }
    return pos + 1;
}

void solve() {
    for (int i = n; i >= 1; i--) {
        h[i] = kth(a[i] + 1);
        operate(h[i], -1);
    }

    for (int i = 1; i <= n; i++) {
        cout << h[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n;

    init();
    solve();
}