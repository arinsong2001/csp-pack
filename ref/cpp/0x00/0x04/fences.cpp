#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, F;
    cin >> N >> F;

    vector<double> arr(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }

    // arr
    // sub range, length >= F
    // let average as av
    // bisect av:
    // arr = [x - av for x in arr]
    //
    // check if exists a sub range whose sum >= 0
    // <=>
    // pref = prefix(arr)
    // check if exists a, b: pref[b] - pref[a - 1] >= 0

    auto check = [&](auto arr, double av) {
        for (auto &x : arr) {
            x -= av;
        }
        double sum = -1e10;
        double min_val = 1e10;
        partial_sum(arr.begin(), arr.end(), arr.begin());
        for (int r = F; r < arr.size(); r++) {
            // for (int l = 1; l <= r - F + 1; l++) {
            //     sum = max(sum, arr[r] - arr[l - 1]);
            // }
            min_val = min(min_val, arr[r - F]);
            sum = max(sum, arr[r] - min_val);
        }
        return sum >= 0;
    };

    double l = 1, r = 2000;
    double mid;

    while (l + 1e-9 < r) {
        mid = (l + r) / 2;
        if (!check(arr, mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    cout << (int)(r * 1000) << endl;
}