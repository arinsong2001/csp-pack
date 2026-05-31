#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    auto arr = views::iota(1, n + 1) | ranges::to<vector<int>>();

    do {
        for (const auto &x : arr) {
            print("{:5}", x);
        }
        println();
    } while (ranges::next_permutation(arr).found);
}