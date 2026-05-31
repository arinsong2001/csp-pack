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
    es[++tot] = {u, w, vs[v].head}, vs[v].head = tot;
}

bool vis[N];

int st, ord[N << 1];

int dep[N];

int sz[N];

const int INF = numeric_limits<int>::max();

int pos, ans = INF;

int cnt = 0, component[N];

void dfs(int u) {
    vis[u] = true;

    ord[++st] = u;

    sz[u] = 1;
    int larger = 0;

    component[u] = cnt;

    for (int i = vs[u].head; i; i = es[i].nxt) {
        auto [v, w, nxt] = es[i];
        if (vis[v]) continue;

        dep[v] = dep[u] + 1;

        dfs(v);

        sz[u] += sz[v];
        larger = max(larger, sz[v]);
    }

    larger = max(larger, n - sz[u]);
    if (larger < ans) pos = u, ans = larger;

    ord[++st] = u;
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

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) cnt++, dfs(i);
    }

    cout << "ord: ", echo(span(ord + 1, st));
    cout << "dep: ", echo(span(dep + 1, n));
    cout << "pos: " << pos << ", " << "ans: " << ans << endl;
    cout << "component: ", echo(span(component + 1, n));
}