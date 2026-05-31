#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    cout << "n: " << n << endl;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    cout << "nums: ";
    for (const auto &x : nums) {
        cout << x << " ";
    }
    cout << endl;

    int m;
    cin >> n >> m;
    cout << "n: " << n << "; " << "m: " << m << endl;

    vector<vector<int>> nums2(n, vector<int>(m));
    for (auto &row : nums2) {
        for (auto &x : row) {
            cin >> x;
        }
    }

    cout << "nums2:" << endl;
    for (const auto &row : nums2) {
        for (const auto &x : row) {
            cout << x << " ";
        }
        cout << "\n";
    }
    cout << flush;

    cout << "gcd(25, 7): " << gcd(25, 7) << endl;
    cout << "lcm(25, 7): " << lcm(25, 7) << endl;

    auto arr = vector{1, 2, 3, 4, 5};

    cout << "arr: ";
    for (const auto &x : arr) {
        cout << x << " ";
    }
    cout << endl;

    cout << "lower: " << lower_bound(arr.begin(), arr.end(), 3) - arr.begin() << endl;
    cout << "upper: " << upper_bound(arr.begin(), arr.end(), 3) - arr.begin() << endl;

    arr.insert(lower_bound(arr.begin(), arr.end(), 3), 3);
    arr.insert(upper_bound(arr.begin(), arr.end(), 3), 3);

    cout << "arr inserted: ";
    for (const auto &x : arr) {
        cout << x << " ";
    }
    cout << endl;

    arr.erase(unique(arr.begin(), arr.end()), arr.end());

    cout << "arr uniqued: ";
    for (const auto &x : arr) {
        cout << x << " ";
    }
    cout << endl;

    mt19937 rng(random_device{}());
    shuffle(arr.begin(), arr.end(), rng);

    cout << "arr shuffled: ";
    for (const auto &x : arr) {
        cout << x << " ";
    }
    cout << endl;

    priority_queue<int, vector<int>, greater<>> h(arr.begin(), arr.end());

    arr.clear();

    while (!h.empty()) {
        arr.push_back(h.top());
        h.pop();
    }

    cout << "arr heap sorted: ";
    for (const auto &x : arr) {
        cout << x << " ";
    }
    cout << endl;

    auto dq = deque(arr.begin(), arr.end());

    dq.push_back(dq.front());
    dq.pop_front();

    rotate(dq.begin(), dq.end() - 1, dq.end());

    cout << "dq: ";
    for (const auto &x : dq) {
        cout << x << " ";
    }
    cout << endl;

    auto vers = vector{"start", "a", "b", "end"};
    map<string, int> ids;
    for (int i = 0; i < vers.size(); i++) {
        ids[vers[i]] = i;
    }

    n = vers.size();

    vector<vector<pii>> g(n);
    g[ids["start"]].push_back({ids["a"], 6});
    g[ids["start"]].push_back({ids["b"], 2});
    g[ids["a"]].push_back({ids["end"], 1});
    g[ids["b"]].push_back({ids["a"], 3});
    g[ids["b"]].push_back({ids["end"], 5});

    const int INF = 0x3f3f3f3f;

    auto dijkstra = [&](string start = "start", string end = "end") {
        int st = ids[start], ed = ids[end];

        vector<int> dist(n, INF);
        dist[st] = 0;

        priority_queue<pii, vector<pii>, greater<>> h;
        h.push({0, st});

        // vector<char> vis(n);

        vector<int> pars(n, -1);

        while (!h.empty()) {
            auto [d, u] = h.top();
            h.pop();

            // if (vis[u]) {
            //     continue;
            // }
            // vis[u] = true;

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

        vector<int> path{ed};
        int curr = ed;
        while (pars[curr] != -1) {
            path.push_back(pars[curr]);
            curr = pars[curr];
        }
        reverse(path.begin(), path.end());

        cout << vers[path[0]];
        for (int i = 1; i < path.size(); i++) {
            cout << " -> " << vers[path[i]];
        }
        cout << endl;
    };

    cout << "dijkstra: ";
    dijkstra();

    auto SPFA = [&](string start = "start", string end = "end") {
        int st = ids[start], ed = ids[end];

        vector<int> dist(n, INF);
        dist[st] = 0;

        deque<int> q{st};

        vector<char> in_queue(n);
        in_queue[st] = true;

        vector<int> pars(n, -1);

        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            in_queue[u] = false;

            for (const auto &[v, w] : g[u]) {
                int nd = dist[u] + w;
                if (nd < dist[v]) {
                    dist[v] = nd;
                    if (!in_queue[v]) {
                        if (!q.empty() && dist[v] < dist[q.front()]) {
                            q.push_front(v);
                        } else {
                            q.push_back(v);
                        }
                        in_queue[v] = true;
                    }
                    pars[v] = u;
                }
            }
        }

        if (dist[ed] == INF) {
            cout << "unreachable!" << endl;
            return;
        }

        vector<int> path{ed};
        int curr = ed;
        while (pars[curr] != -1) {
            path.push_back(pars[curr]);
            curr = pars[curr];
        }
        reverse(path.begin(), path.end());

        cout << vers[path[0]];
        for (int i = 1; i < path.size(); i++) {
            cout << " -> " << vers[path[i]];
        }
        cout << endl;
    };

    cout << "SPFA: ";
    SPFA();

    auto arr_p(arr);
    arr_p.insert(arr_p.begin(), 0);

    auto prefix = [](const vector<int> &arr_p) {
        vector<int> pref(arr_p.size());
        partial_sum(arr_p.begin(), arr_p.end(), pref.begin());
        return pref;
    };

    auto query = [](const vector<int> &pref, int l, int r) {
        return pref[r] - pref[l - 1];
    };

    auto differ = [](const vector<int> &arr_p) {
        vector<int> diff(arr_p.size());
        adjacent_difference(arr_p.begin(), arr_p.end(), diff.begin());
        return diff;
    };

    auto operate = [](vector<int> &diff, int l, int r, int v) {
        diff[l] += v;
        if (r + 1 < diff.size()) {
            diff[r + 1] -= v;
        }
    };

    auto pref = prefix(arr_p);

    cout << "query: " << query(pref, 2, 4) << endl;

    auto diff = differ(arr_p);

    vector<int> restored;

    operate(diff, 2, 4, 1);
    restored = prefix(diff);

    cout << "restored: ";
    for (int i = 1; i < restored.size(); i++) {
        cout << restored[i] << " ";
    }
    cout << endl;

    operate(diff, 2, 4, -1);
    restored = prefix(diff);

    cout << "restored: ";
    for (int i = 1; i < restored.size(); i++) {
        cout << restored[i] << " ";
    }
    cout << endl;

    vector<vector<int>> mat(5, vector<int>(5));
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            mat[i][j] = 5 * i + j + 1;
        }
    }

    vector<vector<int>> mat_p(6, vector<int>(6));
    for (int i = 1; i < mat_p.size(); i++) {
        for (int j = 1; j < mat_p[0].size(); j++) {
            mat_p[i][j] = mat[i - 1][j - 1];
        }
    }

    auto prefix2 = [](const vector<vector<int>> &mat_p) {
        vector<vector<int>> pref2(mat_p);
        for (auto &row : pref2) {
            partial_sum(row.begin(), row.end(), row.begin());
        }

        vector<vector<int>> trans(pref2[0].size(), vector<int>(pref2.size()));
        for (int j = 0; j < trans.size(); j++) {
            for (int i = 0; i < trans[0].size(); i++) {
                trans[j][i] = pref2[i][j];
            }
        }

        for (auto &col : trans) {
            partial_sum(col.begin(), col.end(), col.begin());
        }

        for (int i = 0; i < pref2.size(); i++) {
            for (int j = 0; j < pref2[0].size(); j++) {
                pref2[i][j] = trans[j][i];
            }
        }

        return pref2;
    };

    auto query2 = [](const vector<vector<int>> &pref2, int i1, int j1, int i2, int j2) {
        return pref2[i2][j2] - pref2[i1 - 1][j2] - pref2[i2][j1 - 1] + pref2[i1 - 1][j1 - 1];
    };

    auto differ2 = [](const vector<vector<int>> &mat_p) {
        vector<vector<int>> diff2(mat_p);
        for (auto &row : diff2) {
            adjacent_difference(row.begin(), row.end(), row.begin());
        }

        vector<vector<int>> trans(diff2[0].size(), vector<int>(diff2.size()));
        for (int j = 0; j < trans.size(); j++) {
            for (int i = 0; i < trans[0].size(); i++) {
                trans[j][i] = diff2[i][j];
            }
        }

        for (auto &col : trans) {
            adjacent_difference(col.begin(), col.end(), col.begin());
        }

        for (int i = 0; i < diff2.size(); i++) {
            for (int j = 0; j < diff2[0].size(); j++) {
                diff2[i][j] = trans[j][i];
            }
        }

        return diff2;
    };

    auto operate2 = [](vector<vector<int>> &diff2, int i1, int j1, int i2, int j2, int v) {
        for (const auto &[i, si] : {pair{i1, 1}, pair{i2 + 1, -1}}) {
            if (i >= diff2.size()) {
                continue;
            }
            for (const auto &[j, sj] : {pair{j1, 1}, pair{j2 + 1, -1}}) {
                if (j >= diff2[0].size()) {
                    continue;
                }
                diff2[i][j] += v * si * sj;
            }
        }
    };

    auto pref2 = prefix2(mat_p);

    cout << "query2: " << query2(pref2, 2, 2, 4, 4) << endl;

    auto diff2 = differ2(mat_p);

    vector<vector<int>> restored2;

    operate2(diff2, 2, 2, 4, 4, 1);
    restored2 = prefix2(diff2);

    cout << "restored2:" << endl;
    for (int i = 1; i < restored2.size(); i++) {
        for (int j = 1; j < restored2[0].size(); j++) {
            cout << restored2[i][j] << " ";
        }
        cout << "\n";
    }
    cout << flush;

    operate2(diff2, 2, 2, 4, 4, -1);
    restored2 = prefix2(diff2);

    cout << "restored2:" << endl;
    for (int i = 1; i < restored2.size(); i++) {
        for (int j = 1; j < restored2[0].size(); j++) {
            cout << restored2[i][j] << " ";
        }
        cout << "\n";
    }
    cout << flush;

    arr.erase(arr.begin() + 3, arr.end());
    sort(arr.begin(), arr.end());

    do {
        cout << "perm: ";
        for (const auto &x : arr) {
            cout << x << " ";
        }
        cout << endl;
    } while (next_permutation(arr.begin(), arr.end()));

    auto fib = [](auto &&self, int n) -> ll {
        static vector<ll> memo(100, -1);
        if (n < 2) {
            return n;
        }
        if (memo[n] != -1) {
            return memo[n];
        }
        return memo[n] = self(self, n - 1) + self(self, n - 2);
    };

    cout << "fib(40): " << fib(fib, 40) << endl;
}
