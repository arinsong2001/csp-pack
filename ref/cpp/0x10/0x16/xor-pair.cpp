#include <bits/stdc++.h>

using namespace std;

const int N = 31 * 1e5 + 10;

int n;
int arr[N];

int trie[N][2];
int tot = 1;

void insert(int x) {
    int p = 1;
    for (int i = 30; i >= 0; i--) {
        int bit = x >> i & 1;
        if (trie[p][bit] == 0) {
            trie[p][bit] = ++tot;
        }
        p = trie[p][bit];
    }
}

int query(int x) {
    int p = 1;
    int res = 0;
    for (int i = 30; i >= 0; i--) {
        int bit = x >> i & 1;
        if (trie[p][!bit]) {
            p = trie[p][!bit];
            res |= 1 << i;
        } else {
            p = trie[p][bit];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        insert(arr[i]);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, query(arr[i]));
    }

    cout << ans << endl;
}