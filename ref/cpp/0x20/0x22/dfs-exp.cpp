#include <bits/stdc++.h>

using namespace std;

int n;

auto res = vector<int>{};

void dfs(int pos) {
    if (pos > n) {
        for (const auto &x : res) {
            cout << x << ' ';
        }
        cout << '\n';
        return;
    }
    dfs(pos + 1);
    res.push_back(pos);
    dfs(pos + 1);
    res.pop_back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    dfs(1);
}