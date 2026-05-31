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

int dep[N];

void bfs(int u) {
    auto q = deque<int>{};
    q.push_back(u);
    vis[u] = true;
    dep[u] = 0;
    while (!q.empty()) {
        auto u = q.front();
        q.pop_front();
        for (int i = vs[u].head; i; i = es[i].nxt) {
            auto [v, w, nxt] = es[i];
            if (!vis[v]) {
                q.push_back(v);
                vis[v] = true;
                dep[v] = dep[u] + 1;
            }
        }
    }
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

    bfs(1);

    println("dep: {}", span(dep + 1, n));
}