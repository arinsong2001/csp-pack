#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5 + 10;

int n, k;
ll w[N];

struct Node {
    ll weight, depth;
    int children[10], parent;
} ns[N << 1];

int tot = 0;

struct Comp {
    bool operator()(const int &x, const int &y) const {
        return tie(ns[x].weight, ns[x].depth) > tie(ns[y].weight, ns[y].depth);
    }
};

priority_queue<int, vector<int>, Comp> h;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        ns[++tot].weight = w[i];
        h.push(tot);
    }

    auto r = (n - 1) % (k - 1);
    if (r) {
        r = k - 1 - r;
    }

    for (int i = 0; i < r; i++) {
        h.push(++tot);
    }

    ll length = 0, depth = 0;

    while (h.size() > 1) {
        auto p = ++tot;
        for (int i = 0; i < k; i++) {
            auto t = h.top();
            h.pop();
            ns[p].weight += ns[t].weight;
            ns[p].depth = max(ns[p].depth, ns[t].depth + 1);
            ns[p].children[i] = t;
            ns[t].parent = p;
        }
        length += ns[p].weight;
        depth = max(depth, ns[p].depth);
        h.push(p);
    }

    cout << length << endl;
    cout << depth << endl;
}