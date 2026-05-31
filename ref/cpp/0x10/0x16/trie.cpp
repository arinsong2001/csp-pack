#include <bits/stdc++.h>

using namespace std;

const int SIZE = 1010;
int trie[SIZE][26], tot = 1;
bool end[SIZE];

void insert(string str) {
    int len = int(str.length()), p = 1;
    for (int i = 0; i < len; i++) {
        int ch = str[i] - 'a';
        if (trie[p][ch] == 0) {
            trie[p][ch] = ++tot;
        }
        p = trie[p][ch];
    }
    ::end[p] = true;
}

bool search(string str) {
    int len = int(str.length()), p = 1;
    for (int i = 0; i < len; i++) {
        p = trie[p][str[i] - 'a'];
        if (p == 0) {
            return false;
        }
    }
    return ::end[p];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    insert("catcat");
    cout << "has cat? -> " << search("cat") << endl;
    insert("cat");
    cout << "has cat? -> " << search("cat") << endl;
}