#include <bits/stdc++.h>

using namespace std;

int n;
auto frags = vector<int>{};
auto vis = vector<char>{};

int len, cnt;

bool dfs(int pos, int curr_len, int start) {
    if (pos >= cnt) { return true; }
    if (curr_len == len) { return dfs(pos + 1, 0, 0); }
    int last = 0;
    for (int i = start; i < n; i++) {
        if (vis[i] || curr_len + frags[i] > len || frags[i] == last) { continue; }
        vis[i] = true;
        if (dfs(pos, curr_len + frags[i], i + 1)) { return true; }
        last = frags[i];
        vis[i] = false;
        if (curr_len == 0 || curr_len + frags[i] == len) { return false; }
    }
    return false;
}

void solve() {
    int max_val = *max_element(frags.begin(), frags.end());
    int tot_val = accumulate(frags.begin(), frags.end(), 0);
    for (len = max_val; len <= tot_val; len++) {
        if (tot_val % len) { continue; }
        cnt = tot_val / len;
        if (dfs(0, 0, 0)) {
            cout << len << '\n';
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n && n) {
        frags.clear();
        frags.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> frags[i];
        }
        sort(frags.begin(), frags.end(), greater<>{});
        vis.clear();
        vis.resize(n);
        solve();
    }
}