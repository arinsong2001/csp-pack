#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto merge_sort = [&](auto &&self, auto &a, int l, int r, int &cnt) {
        if (l >= r) {
            return;
        }

        int mid = (l + r) >> 1;
        self(self, a, l, mid, cnt);
        self(self, a, mid + 1, r, cnt);

        vector<int> tmp;
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

    int n;
    while (cin >> n) {
        int size = n * n - 1;

        int cnt_a = 0;
        auto a = vector<int>(size + 1);
        for (int i = 0; i < a.size(); i++) {
            cin >> a[i];
        }
        a.erase(find(a.begin(), a.end(), 0));

        int cnt_b = 0;
        auto b = vector<int>(size + 1);
        for (int i = 0; i < b.size(); i++) {
            cin >> b[i];
        }
        b.erase(find(b.begin(), b.end(), 0));

        // merge_sort(a), merge_sort(b)
        // check if (cnt_a & 1) == (cnt_b & 1)
        // print TAK or NIE

        merge_sort(merge_sort, a, 0, size - 1, cnt_a);
        merge_sort(merge_sort, b, 0, size - 1, cnt_b);
        if ((cnt_a & 1) == (cnt_b & 1)) {
            cout << "TAK" << '\n';
        } else {
            cout << "NIE" << '\n';
        }
    }
}