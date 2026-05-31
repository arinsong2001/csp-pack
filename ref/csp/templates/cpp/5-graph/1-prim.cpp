#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<string> vers{"start", "a", "b", "end"};
    int n = vers.size();

    map<string, int> ids;
    for (int i = 1; i <= vers.size(); i++) {
        ids[vers[i - 1]] = i;
    }

    vector<vector<pair<int, int>>> g(n + 1);
    g[ids["start"]].push_back({ids["a"], 6});
    g[ids["start"]].push_back({ids["b"], 2});
    g[ids["a"]].push_back({ids["end"], 1});
    g[ids["b"]].push_back({ids["a"], 3});
    g[ids["b"]].push_back({ids["end"], 5});

    const int INF = 0x3f3f3f3f;

    auto dijkstra = [&](string start = "start", string end = "end") {
        int st = ids[start], ed = ids[end];

        vector<int> dist(n + 1, INF);
        dist[st] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> h;
        h.push({0, st});

        vector<int> pars(n + 1, -1);

        while (!h.empty()) {
            auto [d, u] = h.top();
            h.pop();

            if (dist[u] < d) {
                continue;
            }

            if (u == ed) {
                break;
            }

            for (const auto &[v, w] : g[u]) {
                int nd = d + w;
                if (nd < dist[v]) {
                    dist[v] = nd;
                    h.push({nd, v});
                    pars[v] = u;
                }
            }
        }

        if (dist[ed] == INF) {
            cout << "unreachable!" << endl;
            return;
        }

        deque<int> path{ed};
        int curr = ed;
        while (pars[curr] != -1) {
            path.push_front(pars[curr]);
            curr = pars[curr];
        }

        cout << vers[path[0] - 1];
        for (int i = 1; i < path.size(); i++) {
            cout << " -> " << vers[path[i] - 1];
        }
        cout << endl;
    };

    cout << "dijkstra: ";
    dijkstra();

    auto prim = [&](string start = "start") {
        int st = ids[start];

        vector<int> dist(n + 1, INF);
        dist[st] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> h;
        h.push({0, st});

        vector<char> vis(n + 1);

        int total = 0;

        while (!h.empty()) {
            auto [d, u] = h.top();
            h.pop();

            if (vis[u]) {
                continue;
            }
            vis[u] = true;

            total += d;

            for (const auto &[v, w] : g[u]) {
                if (!vis[v] && w < dist[v]) {
                    dist[v] = w;
                    h.push({w, v});
                }
            }
        }

        return total;
    };

    cout << "prim: " << prim() << endl;
}
