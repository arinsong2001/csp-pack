#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    static int A[100010];
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    sort(A + 1, A + N + 1);
    auto idx = (N + 1) / 2;
    auto pos = A[idx];

    int ans = 0;
    for (int i = 1; i <= N; i++) {
        ans += abs(pos - A[i]);
    }
    cout << ans << endl;
}