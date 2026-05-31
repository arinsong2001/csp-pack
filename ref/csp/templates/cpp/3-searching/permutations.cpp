// 洛谷 P1706: 全排列问题
//
// example:
//
// input:
// 3
//
// output:
//     1    2    3
//     1    3    2
//     2    1    3
//     2    3    1
//     3    1    2
//     3    2    1

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = i + 1;
    }

    do {
        for (auto x : arr) {
            cout << setw(5) << x;
        }
        cout << "\n";
    } while (next_permutation(arr.begin(), arr.end()));
}
