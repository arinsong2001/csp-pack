#include <bits/stdc++.h>

using namespace std;

int n, r;
int init_w[1010], w[1010], p[1010], fa[1010], sz[1010];
vector<int> seq[1010];

struct Node {
    int idx, w, sz;
    bool operator<(const Node &other) const {
        return w * other.sz < other.w * sz;
    }
};

priority_queue<Node> h;

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) {
        return;
    }
    fa[x] = y;
    w[y] += w[x];
    sz[y] += sz[x];
    seq[y].insert(seq[y].end(), seq[x].begin(), seq[x].end());
    h.push({y, w[y], sz[y]});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> r;

    for (int i = 1; i <= n; i++) {
        cin >> init_w[i];
        w[i] = init_w[i];
        fa[i] = i;
        sz[i] = 1;
        seq[i].push_back(i);
        h.push({i, w[i], sz[i]});
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        p[b] = a;
    }

    while (!h.empty()) {
        auto [idx, weight, size] = h.top();
        h.pop();
        if (weight != w[idx] || size != sz[idx] || idx == r) {
            continue;
        }
        unite(idx, p[idx]);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += i * init_w[seq[r][i - 1]];
    }
    cout << ans << endl;
}