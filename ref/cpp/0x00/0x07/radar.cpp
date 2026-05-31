#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, d;
    cin >> n >> d;

    static pair<double, double> islands[1010];
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;

        if (y < d) {
            double off = sqrt(double(d * d) - double(y * y));
            islands[i].first = x - off;
            islands[i].second = x + off;
        } else if (y == d) {
            islands[i].first = x;
            islands[i].second = x;
        } else {
            cout << -1 << endl;
            return 0;
        }
    }

    sort(islands + 1, islands + n + 1);

    int cnt = 0;
    double curr = -1e9;

    double eps = 1e-9;

    for (int i = 1; i <= n; i++) {
        if (islands[i].first > curr + eps) {
            curr = islands[i].second;
            cnt++;
        } else if (islands[i].first + eps < curr) {
            curr = min(curr, islands[i].second);
        }
    }

    cout << cnt << endl;
}