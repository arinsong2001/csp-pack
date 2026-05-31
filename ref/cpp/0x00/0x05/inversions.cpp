#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto arr = views::iota(1, 6) | ranges::to<vector<int>>();

    auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    ranges::shuffle(arr, rng);

    cout << "arr: ";
    ranges::for_each(arr, [&](auto x) { cout << x << ' '; });
    cout << endl;

    int cnt = 0;

    auto merge_sort = [&](auto &&self, span<int> sp) -> void {
        if (sp.size() < 2) {
            return;
        }

        int mid = sp.size() >> 1;
        auto left = sp.subspan(0, mid);
        auto right = sp.subspan(mid);

        self(self, left);
        self(self, right);

        vector<int> tmp;
        tmp.reserve(sp.size());

        int i = 0, j = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                tmp.push_back(left[i++]);
            } else {
                tmp.push_back(right[j++]);
                cnt += left.size() - i;
            }
        }
        while (i < left.size()) {
            tmp.push_back(left[i++]);
        }
        while (j < right.size()) {
            tmp.push_back(right[j++]);
        }

        for (int i = 0; i < sp.size(); i++) {
            sp[i] = tmp[i];
        }
    };

    merge_sort(merge_sort, arr);

    cout << "sorted: ";
    ranges::for_each(arr, [&](auto x) { cout << x << ' '; });
    cout << endl;

    cout << format("cnt of inversions is {}", cnt) << endl;
}