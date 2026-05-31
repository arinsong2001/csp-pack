#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto calc = [&](const vector<ll> &arr, ll n) {
        vector<int> s;
        ll ans = 0;
        for (int i = 1; i <= n + 1; i++) {
            while (!s.empty() && arr[s.back()] > arr[i]) {
                auto t = s.back();
                s.pop_back();
                auto l = s.empty() ? 0 : s.back();
                ans = max(ans, arr[t] * (i - l - 1));
            }
            s.push_back(i);
        }
        return ans;
    };

    int n;
    while (cin >> n && n != 0) {
        vector<ll> arr(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        arr.push_back(0);
        cout << calc(arr, n) << endl;
    }
}