#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto arr = views::iota(1, 6) | ranges::to<vector<int>>();

    auto rng = mt19937();

    ranges::shuffle(arr, rng);

    cout << "arr: ";
    ranges::for_each(arr, [&](auto x) { cout << x << ' '; });
    cout << endl;

    cout << "pref: ";
    vector<int> pref(arr.size());
    partial_sum(arr.begin(), arr.end(), pref.begin());

    ranges::for_each(pref, [&](auto x) { cout << x << ' '; });
    cout << endl;

    auto query = [&](const vector<int> &pref, int T) {
        // seek k: pref[k] <= T && pref[k + 1] > T
        auto p = ranges::partition_point(pref, [&](auto x) { return x <= T; });
        return p - pref.begin() - 1;
    };

    auto query2 = [&](vector<int> pref, int T) {
        pref.insert(pref.begin(), 0);
        int k = 0;
        int p = 1;
        int sum = 0;
        while (p) {
            if (k + p < pref.size() && sum + pref[k + p] - pref[k] <= T) {
                sum += pref[k + p] - pref[k];
                k += p;
                p <<= 1;
            } else {
                p >>= 1;
            }
        }
        return k - 1;
    };

    for (int i = 0; i < 100; i++) {
        assert(query(pref, i) == query2(pref, i));
    }
}