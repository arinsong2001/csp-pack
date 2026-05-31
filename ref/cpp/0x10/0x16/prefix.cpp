#include <bits/stdc++.h>

using namespace std;

const int M = 100010;
int trie[M][26];
int end[M];
int tot = 1;

void insert(string s) {
    int p = 1;
    for (int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        if (trie[p][c] == 0) {
            trie[p][c] = ++tot;
        }
        p = trie[p][c];
    }
    ::end[p]++;
}

int search(string s) {
    int p = 1, ans = 0;
    for (int i = 0; i < s.size(); i++) {
        p = trie[p][s[i] - 'a'];
        ans += ::end[p];
    }
    return ans;
}

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        insert(s);
    }

    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        cout << search(s) << endl;
    }
}