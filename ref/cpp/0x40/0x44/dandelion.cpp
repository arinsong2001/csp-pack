#include <bits/stdc++.h>

using namespace std;

struct Block {
    int l, r;
};

int n, m, cnt, len;

auto a = vector<int>{};
auto vs = vector<int>{};
auto ids = vector<int>{};
auto bs = vector<Block>{};
auto pos = vector<vector<int>>{};
auto modes = vector<vector<int>>{};

int get_freq(int id, int l, int r) {
    const auto &p = pos[id];
    auto st = lower_bound(p.begin(), p.end(), l);
    auto ed = upper_bound(p.begin(), p.end(), r);
    return ed - st;
}

void init() {
    a.resize(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; }

    vs = a;
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());

    ids.resize(n);
    for (int i = 0; i < n; i++) { ids[i] = lower_bound(vs.begin(), vs.end(), a[i]) - vs.begin(); }

    cnt = max(1, (int)sqrt(n * log(n)));
    len = (n + cnt - 1) / cnt;

    bs.resize(cnt);
    for (int i = 0; i < cnt; i++) { bs[i].l = clamp(i * len, 0, n - 1), bs[i].r = clamp((i + 1) * len - 1, 0, n - 1); }

    pos.resize(vs.size());
    for (int i = 0; i < n; i++) { pos[ids[i]].push_back(i); }

    modes.resize(cnt, vector<int>(cnt));
    auto fs = vector<int>(vs.size());
    for (int i = 0; i < cnt; i++) {
        fill(fs.begin(), fs.end(), 0);
        int mode = -1, freq = 0;
        for (int j = i; j < cnt; j++) {
            int l = bs[j].l, r = bs[j].r;
            for (int k = l; k <= r; k++) {
                int id = ids[k], f = ++fs[id];
                if (f > freq || f == freq && id < mode) { mode = id, freq = f; }
            }
            modes[i][j] = mode;
        }
    }
}

int query(int l, int r) {
    static auto vis = vector<int>(vs.size());
    static int timer = 0;
    timer++;

    l--, r--;
    int mode = -1, freq = 0;

    auto update = [&](int id) {
        if (vis[id] == timer) { return; }
        vis[id] = timer;
        int f = get_freq(id, l, r);
        if (f > freq || f == freq && id < mode) { mode = id, freq = f; }
    };

    int p = l / len, q = r / len;
    if (p == q || p + 1 == q) {
        for (int i = l; i <= r; i++) { update(ids[i]); }
    } else if (p + 1 < q) {
        for (int i = l; i <= bs[p].r; i++) { update(ids[i]); }
        update(modes[p + 1][q - 1]);
        for (int i = bs[q].l; i <= r; i++) { update(ids[i]); }
    } else {
        throw runtime_error("p > q !");
    }

    return vs[mode];
}

void solve() {
    int l, r, x = 0;
    for (int i = 0; i < m; i++) {
        cin >> l >> r;
        l = (l + x - 1) % n + 1;
        r = (r + x - 1) % n + 1;
        if (l > r) { swap(l, r); }
        x = query(l, r);
        cout << x << '\n';
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