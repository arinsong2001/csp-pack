#include <bits/stdc++.h>

using namespace std;

const int N = 1010, M = 1010; // less than about N verts & M edges

int head[N];

struct Edge {
    int to, weight, next;
} es[M];

int tot = 1; // start from 2, for pairwise transformation

void add(int x, int y, int z) {
    es[++tot] = {y, z, head[x]};
    head[x] = tot;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> names{"start", "a", "b", "end"};

    int n = names.size();

    unordered_map<string, int> ids;
    for (int i = 0; i < n; i++) {
        ids[names[i]] = i;
    }

    add(ids["start"], ids["a"], 6);
    add(ids["a"], ids["start"], 6);

    add(ids["start"], ids["b"], 2);
    add(ids["b"], ids["start"], 2);

    add(ids["a"], ids["end"], 1);
    add(ids["end"], ids["a"], 1);

    add(ids["b"], ids["a"], 3);
    add(ids["a"], ids["b"], 3);

    add(ids["b"], ids["end"], 5);
    add(ids["end"], ids["b"], 5);

    auto dijkstra = [&](int start, int end) {
        vector<int> dist(n, numeric_limits<int>::max());
        dist[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> h;
        h.push({0, start});

        vector<int> fa(n, -1);

        while (!h.empty()) {
            auto [d, u] = h.top();
            h.pop();

            if (dist[u] < d) {
                continue;
            }

            if (u == end) {
                break;
            }

            auto e = head[u];
            while (e != 0) {
                auto [v, w, nxt] = es[e];
                auto nd = d + w;
                if (nd < dist[v]) {
                    dist[v] = nd;
                    h.push({nd, v});
                    fa[v] = u;
                }
                e = nxt;
            }
        }

        if (dist[end] == numeric_limits<int>::max()) {
            cout << "unreachable!" << endl;
            return;
        }

        vector<int> path;
        path.push_back(end);

        auto curr = end;
        while (fa[curr] != -1) {
            path.push_back(fa[curr]);
            curr = fa[curr];
        }

        reverse(path.begin(), path.end());
        cout << names[path[0]];
        for (int i = 1; i < path.size(); i++) {
            cout << " -> " << names[path[i]];
        }
        cout << endl;
    };

    dijkstra(ids["start"], ids["end"]);
}