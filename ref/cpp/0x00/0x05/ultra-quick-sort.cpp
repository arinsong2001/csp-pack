#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    static ll a[500010];

    ll cnt;

    // auto merge_sort = [&](auto &&self, span<ll> sp) -> void {
    //     if (sp.size() < 2) {
    //         return;
    //     }

    //     int mid = sp.size() / 2;
    //     auto left = sp.subspan(0, mid);
    //     auto right = sp.subspan(mid);

    //     self(self, left);
    //     self(self, right);

    //     vector<ll> tmp;
    //     tmp.reserve(sp.size());

    //     int i = 0, j = 0;
    //     while (i < left.size() && j < right.size()) {
    //         if (left[i] <= right[j]) {
    //             tmp.push_back(left[i++]);
    //         } else {
    //             tmp.push_back(right[j++]);
    //             cnt += left.size() - i;
    //         }
    //     }
    //     while (i < left.size()) {
    //         tmp.push_back(i++);
    //     }
    //     while (j < right.size()) {
    //         tmp.push_back(j++);
    //     }

    //     for (int i = 0; i < sp.size(); i++) {
    //         sp[i] = tmp[i];
    //     }
    // };

    auto merge_sort = [&](auto &&self, auto &a, int l, int r) {
        if (l >= r) {
            return;
        }

        int mid = (l + r) >> 1;
        self(self, a, l, mid);
        self(self, a, mid + 1, r);

        vector<ll> tmp;
        tmp.reserve(r - l + 1);

        int i = l, j = mid + 1;
        while (i <= mid && j <= r) {
            if (a[i] <= a[j]) {
                tmp.push_back(a[i++]);
            } else {
                tmp.push_back(a[j++]);
                cnt += mid - i + 1;
            }
        }
        while (i <= mid) {
            tmp.push_back(a[i++]);
        }
        while (j <= r) {
            tmp.push_back(a[j++]);
        }

        for (int i = 0; i < tmp.size(); i++) {
            a[l + i] = tmp[i];
        }
    };

    while (cin >> n && n) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        cnt = 0;
        // merge_sort(merge_sort, span(a, n));
        merge_sort(merge_sort, a, 0, n - 1);
        cout << cnt << '\n';
    }
}