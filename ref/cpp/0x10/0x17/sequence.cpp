#include <bits/stdc++.h>

using namespace std;

struct Node {
    int i, j;
    bool last;
    int sum;
    bool operator>(const Node &other) const {
        return sum > other.sum;
    }
};

int t, m, n;

vector<int> exec(vector<int> a, vector<int> b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    priority_queue<Node, vector<Node>, greater<>> h;
    h.push({0, 0, false, a[0] + b[0]});

    vector<int> res;

    auto n = a.size();
    for (int k = 0; k < n; k++) {
        auto [i, j, last, sum] = h.top();
        h.pop();
        res.push_back(sum);
        h.push({i, j + 1, true, j + 1 < n ? a[i] + b[j + 1] : a[i]});
        if (!last) {
            h.push({i + 1, j, false, i + 1 < n ? a[i + 1] + b[j] : b[j]});
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> t;
    while (t--) {
        cin >> m >> n;
        vector<vector<int>> seqs(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> seqs[i][j];
            }
        }

        auto tmp = seqs[0];
        for (int i = 1; i < seqs.size(); i++) {
            tmp = exec(tmp, seqs[i]);
        }

        sort(tmp.begin(), tmp.end());

        for (const auto &x : tmp) {
            cout << x << ' ';
        }
        cout << endl;
    }
}