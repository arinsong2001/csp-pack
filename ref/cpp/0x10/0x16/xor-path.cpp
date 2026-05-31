#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
const int M = 3.1e6 + 10;

int n;

int head[N];

struct Edge {
    int to, w, nxt;
} es[N << 1];

int tot = 1;

void add(int u, int v, int w) {
    es[++tot] = {v, w, head[u]};
    head[u] = tot;
    es[++tot] = {u, w, head[v]};
    head[v] = tot;
}

int D[N];

void dfs(int u, int fa) {
    auto t = head[u];
    while (t) {
        auto [v, w, nxt] = es[t];
        if (v == fa) {
            t = nxt;
            continue;
        }
        D[v] = D[u] ^ w;
        dfs(v, u);
        t = nxt;
    }
}

int trie[M][2];
int tr_tot = 1;

void insert(int x) {
    int p = 1;
    for (int i = 30; i >= 0; i--) {
        int bit = x >> i & 1;
        if (!trie[p][bit]) {
            trie[p][bit] = ++tr_tot;
        }
        p = trie[p][bit];
    }
}

int query(int x) {
    int p = 1;
    int res = 0;
    for (int i = 30; i >= 0; i--) {
        int bit = x >> i & 1;
        if (trie[p][!bit]) {
            p = trie[p][!bit];
            res |= 1 << i;
        } else {
            p = trie[p][bit];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
    }

    dfs(es[2].to, -1);

    for (int i = 0; i < n; i++) {
        insert(D[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, query(D[i]));
    }

    cout << ans << endl;
}