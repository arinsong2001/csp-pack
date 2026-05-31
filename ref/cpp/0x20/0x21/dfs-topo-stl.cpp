#include <bits/stdc++.h>

using namespace std;

const int N = 10010;

auto g = vector<vector<pair<int, int>>>(N);

auto vs = set<int>{};

void add(int u, int v, int w) {
    vs.insert(u), vs.insert(v);
    g[u].push_back({v, w});
}

auto path = vector<int>{};

auto vis = vector<int>(N);

bool has_cycle;

void dfs(int u) {
    vis[u] = 1;
    for (auto [v, w] : g[u]) {
        if (vis[v] == 1) {
            has_cycle = true;
            return;
        }
        if (vis[v] == 2) { continue; }
        dfs(v);
        if (has_cycle) { return; }
    }
    vis[u] = 2;
    path.push_back(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    add(1, 2, 6);
    add(1, 3, 2);
    add(2, 4, 1);
    add(3, 2, 3);
    add(3, 4, 5);

    for (auto x : vs) {
        if (!vis[x]) { dfs(x); }
        if (has_cycle) { break; }
    }

    if (has_cycle) {
        cout << "has cycle!" << endl;
    } else {
        println("{}", path | views::reverse);
    }
}