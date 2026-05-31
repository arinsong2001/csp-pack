#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int a[N];
int prv[N], nxt[N];
bool del[N];

struct Comp {
    bool operator()(int x, int y) const {
        return a[x] > a[y];
    }
};

priority_queue<int, vector<int>, Comp> h;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // construct diff during the input
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i - 1] = a[i] - a[i - 1];
    }
    // sentinel -> trickery!
    a[0] = a[n] = 0x3f3f3f3f;

    for (int i = 1; i < n; i++) {
        h.push(i);
        prv[i] = i - 1;
        nxt[i] = i + 1;
    }

    int ans = 0;

    while (k--) {
        auto t = h.top();
        h.pop();

        while (del[t]) {
            t = h.top();
            h.pop();
        }

        ans += a[t];

        // <=> erase p, then insert q
        a[t] = a[prv[t]] + a[nxt[t]] - a[t];

        // lazy deletion, then insert q
        del[prv[t]] = del[nxt[t]] = 1;
        h.push(t);

        // maintain doubly linked list
        prv[t] = prv[prv[t]];
        nxt[t] = nxt[nxt[t]];
        nxt[prv[t]] = prv[nxt[t]] = t;
    }

    cout << ans << endl;
}