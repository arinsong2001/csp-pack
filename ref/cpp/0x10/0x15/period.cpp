#include <bits/stdc++.h>

using namespace std;

int n;
string s;
vector<int> nxt;

void prewarm() {
    nxt.clear();
    nxt.resize(s.size());
    nxt[0] = -1;
    for (int i = 1, j = -1; i < s.size(); i++) {
        while (j >= 0 && s[i] != s[j + 1]) {
            j = nxt[j];
        }
        if (s[i] == s[j + 1]) {
            j++;
        }
        nxt[i] = j;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    int id = 1;
    while (cin >> n && n) {
        cout << "Test case #" << id++ << endl;
        cin >> s;
        prewarm();
        for (int i = 0; i < s.size(); i++) {
            // s[0, i] -> sub
            // !(size % len)
            // !((i + 1) % (i - j))
            int j = nxt[i];
            if (j >= 0 && !((i + 1) % (i - j))) {
                cout << i + 1 << ' ' << (i + 1) / (i - j) << endl;
            }
        }
        cout << endl;
    }
}