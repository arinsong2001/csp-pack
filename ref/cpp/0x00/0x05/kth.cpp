#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto arr = views::iota(1, 6) | ranges::to<vector<int>>();

    auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    ranges::shuffle(arr, rng);

    int k = 2;

    auto randint = [&](int l, int r) {
        return (int)(l + rng() % (r - l + 1));
    };

    auto kth = [&](auto &&self, span<int> sp, int k) -> int {
        if (sp.size() == 0) {
            throw runtime_error("sp.size() == 0");
        }
        if (sp.size() == 1) {
            return sp[0];
        }

        int idx = randint(0, sp.size() - 1);
        int pivot = sp[idx];

        auto ge = ranges::partition(sp, [&](auto x) { return x < pivot; });
        auto g = ranges::partition(ge, [&](auto x) { return x == pivot; });

        int r_size = g.size();
        int m_size = ge.size() - g.size();
        int l_size = sp.size() - ge.size();

        if (k < l_size) {
            return self(self, sp.subspan(0, l_size), k);
        } else if (k >= ge.size()) {
            return self(self, sp.subspan(ge.size()), k);
        } else {
            return pivot;
        }
    };

    cout << kth(kth, arr, k) << endl;
}