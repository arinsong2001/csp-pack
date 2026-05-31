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

int deg[N];

void add(int u, int v, int w = 1) {
    es[++tot] = {v, w, vs[u].head}, vs[u].head = tot;
    deg[v]++;
}

optional<vector<int>> topo_sort(int n) {
    auto res = vector<int>{};
    auto q = deque<int>{};
    auto deg = vector<int>(::deg, ::deg + n + 1);
    for (int i = 1; i <= n; i++) {
        if (!deg[i]) {
            q.push_back(i);
        }
    }
    while (!q.empty()) {
        auto u = q.front();
        q.pop_front();
        res.push_back(u);
        for (int i = vs[u].head; i; i = es[i].nxt) {
            auto [v, w, nxt] = es[i];
            if (!--deg[v]) {
                q.push_back(v);
            }
        }
    }
    if (res.size() >= n) return res;
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