#include <bits/stdc++.h>

using namespace std;

#define int long long

struct Block {
    int l, r;
    int sum, add;
};

int n, m, len, cnt;

auto a = vector<int>{};
auto bs = vector<Block>{};

void init() {
    a.resize(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; }

    len = sqrt(n);
    cnt = n / len + bool(n % len);

    bs.resize(cnt);
    for (int i = 0; i < cnt; i++) {
        bs[i].l = i * len, bs[i].r = (i + 1) * len - 1;
        for (int j = 0; j < len; j++) { bs[i].sum += a[i * len + j]; }
    }
}

int get_block(int i) { return i / len; }

void solve(int l, int r, int d) {
    l--, r--;
    int p = get_block(l), q = get_block(r);
    if (p == q) {
        for (int i = l; i <= r; i++) { a[i] += d; }
        bs[p].sum += d * (r - l + 1);
    } else if (p < q) {
        for (int i = l; i <= bs[p].r; i++) { a[i] += d; }
        bs[p].sum += d * (bs[p].r - l + 1);
        for (int i = p + 1; i <= q - 1; i++) { bs[i].add += d; }
        for (int i = bs[q].l; i <= r; i++) { a[i] += d; }
        bs[q].sum += d * (r - bs[q].l + 1);
    } else {
        throw runtime_error("p > q at cmd C!");
    }
}

void solve(int l, int r) {
    l--, r--;
    int p = get_block(l), q = get_block(r);
    int ans = 0;
    if (p == q) {
        for (int i = l; i <= r; i++) { ans += a[i]; }
        ans += bs[p].add * (r - l + 1);
    } else if (p < q) {
        for (int i = l; i <= bs[p].r; i++) { ans += a[i]; }
        ans += bs[p].add * (bs[p].r - l + 1);
        for (int i = p + 1; i <= q - 1; i++) { ans += bs[i].sum + bs[i].add * len; }
        for (int i = bs[q].l; i <= r; i++) { ans += a[i]; }
        ans += bs[q].add * (r - bs[q].l + 1);
    } else {
        throw runtime_error("p > q at cmd Q!");
    }
    cout << ans << '\n';
}

void solve() {
    for (int i = 0; i < m; i++) {
        char cmd;
        cin >> cmd;
        if (cmd == 'C') {
            int l, r, d;
            cin >> l >> r >> d;
            solve(l, r, d);
        } else if (cmd == 'Q') {
            int l, r;
            cin >> l >> r;
            solve(l, r);
        } else {
            throw runtime_error("wrong cmd!");
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n >> m;

    init();
    solve();
}