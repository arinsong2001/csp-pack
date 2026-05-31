#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int n;

auto ys = vector<int>{};

auto c = vector<int>{};

auto ls = vector<int>{};
auto gr = vector<int>{};
auto rev_ls = vector<int>{};
auto rev_gr = vector<int>{};

int ask(int i) {
    int ans = 0;
    for (; i; i -= i & -i) { ans += c[i]; }
    return ans;
}

int query(int l, int r) {
    return ask(r) - ask(l - 1);
}

void add(int i, int v) {
    for (; i <= n; i += i & -i) { c[i] += v; }
}

void init() {
    ys.resize(n + 1);
    for (int i = 1; i <= n; i++) { cin >> ys[i]; }

    c.resize(n + 1);

    ls.resize(n + 1);
    gr.resize(n + 1);
    rev_ls.resize(n + 1);
    rev_gr.resize(n + 1);
}

void solve() {
    for (int i = 1; i <= n; i++) {
        int y = ys[i];
        ls[i] = query(1, y - 1);
        gr[i] = query(y + 1, n);
        add(y, 1);
    }

    c.clear();
    c.resize(n + 1);

    for (int i = n; i >= 1; i--) {
        int y = ys[i];
        rev_ls[i] = query(1, y - 1);
        rev_gr[i] = query(y + 1, n);
        add(y, 1);
    }

    ll cnt_V = 0, cnt_A = 0;
    for (int i = 1; i <= n; i++) {
        cnt_V += (ll)gr[i] * rev_gr[i];
        cnt_A += (ll)ls[i] * rev_ls[i];
    }

    cout << cnt_V << ' ' << cnt_A << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n;

    init();
    solve();
}