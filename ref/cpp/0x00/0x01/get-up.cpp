#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m;
string ops[N];
int ts[N];

void trans(int &operand, int cmd) {
    if (ops[cmd] == "AND") {
        operand &= ts[cmd];
    } else if (ops[cmd] == "XOR") {
        operand ^= ts[cmd];
    } else if (ops[cmd] == "OR") {
        operand |= ts[cmd];
    } else {
        throw runtime_error("wrong operator!");
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("1.in", "r", stdin);

    cin >> n >> m;

    int zero = 0;
    int one = numeric_limits<int>::max();

    for (int i = 0; i < n; i++) {
        cin >> ops[i] >> ts[i];
        trans(zero, i);
        trans(one, i);
    }

    int ans = 0;

    for (int i = 30; i >= 0; i--) {
        // ith bit of ans: 0->1 if and only if (trans-ed ans <= m && 0->0 && 1->1)
        if (ans + (1 << i) <= m && (zero >> i & 1) == 0 && (one >> i & 1) == 1) {
            ans += (1 << i);
        }
    }

    for (int i = 0; i < n; i++) {
        trans(ans, i);
    }

    cout << ans << endl;
}