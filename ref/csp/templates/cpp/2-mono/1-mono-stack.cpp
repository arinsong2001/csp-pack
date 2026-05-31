#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    stack<int> s;
    vector<int> res(n + 1);

    // 遍历arr
    for (int i = 1; i <= n; i++) {
        // pop, 维持单调性
        while (!s.empty() && a[s.top()] < a[i]) {
            int tmp = s.top();
            s.pop();
            // 存答案
            res[tmp] = i;
        }
        // push arr[i]
        s.push(i);
    }

    for (int i = 1; i <= n; i++) {
        cout << res[i] << " ";
    }
    cout << "\n";
}
