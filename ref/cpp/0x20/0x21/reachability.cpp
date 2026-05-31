#include <bits/stdc++.h>

using namespace std;

int n, m;

const int N = 30010;

struct Vert {
    int head;
} vs[N];

struct Edge {
    int v, nxt;
} es[N];

int tot = 1;

int deg[N];

void add(int u, int v) {
    es[++tot] = {v, vs[u].head}, vs[u].head = tot;
    deg[v]++;
}

auto f = vector<bitset<N>>(N);

auto topo_order = vector<int>{};

bool topo_sort() {
    auto q = deque<int>{};

    for (int i = 1; i <= n; i++) {
        if (!deg[i]) {
            q.push_back(i);
        }
    }

    while (!q.empty()) {
        auto u = q.front();
        q.pop_front();
        topo_order.push_back(u);

        for (int i = vs[u].head; i; i = es[i].nxt) {
            auto [v, nxt] = es[i];
            if (!--deg[v]) {
                q.push_back(v);
            }
        }
    }

    return topo_order.size() == n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("1.in", "r", stdin);

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        add(x, y);
    }

    bool has_cycle = !topo_sort();
    assert(!has_cycle);

    auto order = topo_order;
    reverse(order.begin(), order.end());

    for (const auto &x : order) {
        f[x].set(x);
        for (int i = vs[x].head; i; i = es[i].nxt) {
            auto [v, nxt] = es[i];
            f[x] |= f[v];
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << f[i].count() << '\n';
    }
}