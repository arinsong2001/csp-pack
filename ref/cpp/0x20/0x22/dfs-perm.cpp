#include <bits/stdc++.h>

using namespace std;

int n;

int order[20];
bool chosen[20];

void dfs(int pos) {
    if (pos > n) {
        for (int i = 1; i <= n; i++) {
            cout << order[i] << ' ';
        }
        cout << '\n';
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (chosen[i]) {
            continue;
        }
        order[pos] = i;
        chosen[i] = true;
        dfs(pos + 1);
        chosen[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // dfs(1);

    auto arr = vector<int>(n);
    iota(arr.begin(), arr.end(), 1);

    do {
        for (const auto &x : arr) {
            cout << x << ' ';
        }
        cout << '\n';
    } while (next_permutation(arr.begin(), arr.end()));
}