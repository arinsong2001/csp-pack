#include <bits/stdc++.h>

using namespace std;

struct Task {
    int a, b;
};

int n, m;

int tot_t = 0, tot_f = 0, tot_n = 0;

auto ts_flex = vector<Task>{};
auto ts_norm = vector<Task>{};

void init() {
    int o, t, a, b;
    for (int i = 0; i < n; i++) {
        cin >> o >> t >> a >> b;
        if (o == 0) { ts_flex.push_back({a, b}), tot_f += a; }
        if (o == 1) { ts_norm.push_back({a, b}), tot_n += a; }
        tot_t += t;
    }

    auto comp = [](const Task &t1, const Task &t2) { return 1.0 * t1.b / t1.a > 1.0 * t2.b / t2.a; };
    sort(ts_flex.begin(), ts_flex.end(), comp);
    sort(ts_norm.begin(), ts_norm.end(), comp);
}

double get_f_value(int cnt) {
    double ans = 0;
    for (const auto &[a, b] : ts_flex) {
        if (cnt >= a) {
            ans += b;
            cnt -= a;
        } else {
            assert(a > 0);
            ans += 1.0 * cnt * b / a;
            cnt -= cnt;
        }
        if (!cnt) { break; }
    }
    return ans;
}

void solve() {
    // quantity: a[i]
    // value per item: b[i] / a[i]

    double max_v = 0;

    auto f = vector<int>(m + 1);
    for (const auto &[a, b] : ts_norm) {
        for (int i = m; i >= a; i--) { f[i] = max(f[i], f[i - a] + b); }
    }

    for (int i = 0; i <= m; i++) {
        double v = f[i] + get_f_value(m - i);
        max_v = max(max_v, v);
    }

    cout << fixed << setprecision(6) << tot_t - max_v << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n >> m;

    init();
    solve();
}