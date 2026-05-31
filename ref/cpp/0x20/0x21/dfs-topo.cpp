#include <bits/stdc++.h>

using namespace std;

void type(auto &&...args) {
    cout << __PRETTY_FUNCTION__ << endl;
}

void echo(auto &&...args) {
    ((cout << format("{} ", args)), ...);
    cout << endl;
}

auto concat(ranges::input_range auto &&...args) {
    auto res = vector<common_type_t<ranges::range_value_t<remove_cvref_t<decltype(args)>>...>>{};
    (res.insert(res.end(), ranges::begin(args), ranges::end(args)), ...);
    return res;
}

const int N = 1010;
int n;

struct Vert {
    int head;
} vs[N];

struct Edge {
    int v, w, nxt;
} es[N << 1];

int tot = 1;

void add(int u, int v, int w = 1) {
    es[++tot] = {v, w, vs[u].head}, vs[u].head = tot;
}

int vis[N];

optional<vector<int>> topo_sort(int n) {
    auto res = vector<int>{};
    bool has_cycle = false;
    auto dfs = [&](auto &&self, int u) {
        vis[u] = 1;
        for (int i = vs[u].head; i; i = es[i].nxt) {
            auto [v, w, nxt] = es[i];
            if (vis[v] == 1) return false;
            if (vis[v] == 2) continue;
            if (!self(self, v)) return false;
        }
        vis[u] = 2;
        res.push_back(u);
        return true;
    };
    for (int i = 1; i <= n && !has_cycle; i++) {
        if (!vis[i]) {
            has_cycle = !dfs(dfs, i);
        }
    }
    ranges::reverse(res);
    if (!has_cycle) return res;
    return nullopt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    n = 9;

    add(1, 2);
    add(1, 4);
    add(1, 7);
    add(2, 5);
    add(2, 8);
    add(3, 9);
    add(4, 3);
    add(4, 6);

    auto opt = topo_sort(n);
    auto ans = opt ? format("topo: {}", opt.value()) : "has cycle!";
    cout << ans << endl;
}