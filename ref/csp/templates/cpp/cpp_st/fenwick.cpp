#include <bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 1010;

int n; // arr's size (1-based)

ll tr[N];

// 单点加
void add(ll tr[], int x, ll v) {
    for (; x <= n; x += x & -x) {
        tr[x] += v;
    }
}

// 前缀和
ll pref(ll tr[], int x) {
    ll ans = 0;
    for (; x > 0; x -= x & -x) {
        ans += tr[x];
    }
    return ans;
}

ll query(ll tr[], int l, int r) {
    return pref(tr, r) - pref(tr, l - 1);
}

// point add, range query -> add(x, v), pref(r) - pref(l - 1)
// range add, point query -> maintain diff of arr, add(l, v), add(r + 1, -v), pref(x)

// range add, range query:
// maintain diff & diff * i

ll tr1[N], tr2[N];

void range_add(int l, int r, ll v) {
    add(tr1, l, v);
    add(tr1, r + 1, -v);

    add(tr2, l, v * (l - 1));
    add(tr2, r + 1, -v * r);
}

ll range_pref(int x) {
    return x * pref(tr1, x) - pref(tr2, x);
}

ll range_query(int l, int r) {
    return range_pref(r) - range_pref(l - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
