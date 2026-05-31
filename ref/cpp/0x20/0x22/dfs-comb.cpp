#include <bits/stdc++.h>

using namespace std;

int n, m;

auto res = vector<int>{};

void dfs(int pos) {
    if (res.size() > m || res.size() + (n - pos + 1) < m) {
        return;
    }
    if (pos > n) {
        for (const auto &x : res) {
            cout << x << ' ';
        }
        cout << '\n';
        return;
    }
    res.push_back(pos);
    dfs(pos + 1);
    res.pop_back();
    dfs(pos + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    dfs(1);
}