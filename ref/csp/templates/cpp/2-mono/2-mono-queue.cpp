#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    deque<int> q;

    vector<int> min_val;
    min_val.reserve(n);

    vector<int> max_val;
    max_val.reserve(n);

    for (int i = 1; i <= n; i++) {
        while (!q.empty() && q.front() < i - k + 1) {
            q.pop_front();
        }

        while (!q.empty() && a[q.back()] >= a[i]) {
            q.pop_back();
        }

        q.push_back(i);

        if (i >= k) {
            min_val.push_back(a[q.front()]);
        }
    }

    q.clear();

    for (int i = 1; i <= n; i++) {
        while (!q.empty() && q.front() < i - k + 1) {
            q.pop_front();
        }

        while (!q.empty() && a[q.back()] <= a[i]) {
            q.pop_back();
        }

        q.push_back(i);

        if (i >= k) {
            max_val.push_back(a[q.front()]);
        }
    }

    for (const auto &x : min_val) {
        cout << x << " ";
    }
    cout << "\n";

    for (const auto &x : max_val) {
        cout << x << " ";
    }
    cout << "\n";
}
