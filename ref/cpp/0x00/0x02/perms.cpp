#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // static int a[20];
    // iota(a, a + n, 1);
    // do {
    //     for (int i = 0; i < n; i++) {
    //         cout << a[i] << " ";
    //     }
    //     cout << endl;
    // } while (next_permutation(a, a + n));

    // static bool chosen[20];
    // static vector<int> order;
    //
    // int r = n;
    //
    // auto perm = [&](auto &&self, int cnt, int r) -> void {
    //     if (cnt == r) {
    //         for (auto x : order) {
    //             cout << x << ' ';
    //         }
    //         cout << '\n';
    //         return;
    //     }
    //     for (int i = 1; i <= n; i++) {
    //         if (chosen[i]) {
    //             continue;
    //         }
    //         chosen[i] = true;
    //         order.push_back(i);
    //         self(self, cnt + 1, r);
    //         order.pop_back();
    //         chosen[i] = false;
    //     }
    // };
    //
    // perm(perm, 0, r);

    static bool chosen[20];
    static vector<int> order;

    int r = n;
    fill(chosen + 1, chosen + r + 1, 1);

    do {
        order.clear();
        for (int i = 1; i <= n; i++) {
            if (chosen[i]) {
                order.push_back(i);
            }
        }
        do {
            for (auto x : order) {
                cout << x << ' ';
            }
            cout << '\n';
        } while (next_permutation(order.begin(), order.end()));
    } while (prev_permutation(chosen + 1, chosen + n + 1));
}