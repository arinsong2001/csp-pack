#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10;

int n, qtt[N];

priority_queue<int, vector<int>, greater<>> h;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> qtt[i];
        h.push(qtt[i]);
    }

    int ans = 0;

    while (h.size() > 1) {
        auto ts = vector<int>(2);
        for (int i = 0; i < ts.size(); i++) {
            ts[i] = h.top();
            h.pop();
        }
        auto sum = accumulate(ts.begin(), ts.end(), 0);
        ans += sum;
        h.push(sum);
    }

    cout << ans << endl;
}