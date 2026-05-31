#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    static int A[500010];

    int N, M;
    ll T;

    auto calc = [&](int l, int r) -> ll {
        assert(l < r);

        vector<int> tmp(A + l, A + r + 1);
        // ranges::sort(tmp);
        sort(tmp.begin(), tmp.end());

        int mid = tmp.size() >> 1;

        ll sum = 0;
        for (int i = 0; i < mid && i < M; i++) {
            ll sub = tmp[i] - tmp[tmp.size() - 1 - i];
            sum += sub * sub;
        }

        return sum;
    };

    auto seek = [&](int l) -> int {
        int r = l;

        int p = 1;
        while (p) {
            if (r + p < N && calc(l, r + p) <= T) {
                r += p;
                p <<= 1;
            } else {
                p >>= 1;
            }
        }

        return r;
    };

    while (K--) {
        cin >> N >> M >> T;

        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }

        int l = 0, cnt = 0;
        while (l < N) {
            l = seek(l) + 1;
            cnt++;
        }

        cout << cnt << '\n';
    }
}