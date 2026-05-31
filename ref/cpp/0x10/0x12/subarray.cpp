#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int n, m;
ll arr[300010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    ll M = *max_element(arr + 1, arr + n + 1);

    partial_sum(arr + 1, arr + n + 1, arr + 1);

    deque<ll> dq;
    ll ans = numeric_limits<ll>::min();

    dq.push_back(0);

    for (int i = 1; i <= n; i++) {
        while (!dq.empty() && i - dq.front() > m) {
            dq.pop_front();
        }
        ans = max(ans, arr[i] - arr[dq.front()]);
        while (!dq.empty() && arr[dq.back()] >= arr[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }

    cout << ans << endl;
}