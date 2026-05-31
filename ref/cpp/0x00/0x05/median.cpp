#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int P;
    cin >> P;

    static int arr[100010];

    for (int i = 0; i < P; i++) {
        int ord, M;
        cin >> ord >> M;

        for (int i = 1; i <= M; i++) {
            cin >> arr[i];
        }

        // now, data -> arr[1] to arr[M]

        // [1] to [(1 + M) // 2]
        priority_queue<int> h_max;
        // [(1 + M) // 2 + 1] to [M]
        priority_queue<int, vector<int>, greater<>> h;

        vector<int> res;

        // cout << "#######" << endl;
        // for (int i = 1; i <= M; i++) {
        //     cout << arr[i] << ' ';
        // }
        // cout << endl;
        // cout << "#######" << endl;

        for (int i = 1; i <= M; i++) {
            if (h_max.empty() || arr[i] <= h_max.top()) {
                // cout << "h_max.push(" << arr[i] << ")" << endl;
                h_max.push(arr[i]);
            } else {
                // cout << format("h.push({}", arr[i]) << endl;
                h.push(arr[i]);
            }

            // !! don't code like this: if (h_max.size() - h.size() > 1) { ...; }
            // xxx.size() -> size_t aka unsigned long
            // `h_max.size() - h.size()` could lead to an overflow!
            // horrible subtraction!
            if (h_max.size() > h.size() + 1) {
                // cout << "h_max.size() is too big!" << endl;
                // cout << format("h.push({})", h_max.top()) << endl;
                h.push(h_max.top());
                h_max.pop();
            } else if (h_max.size() < h.size()) {
                // cout << "h.size() is too big!" << endl;
                // cout << format("h_max.push({})", h.top()) << endl;
                h_max.push(h.top());
                h.pop();
            }

            if (i & 1) {
                // cout << format("odd, res.push({})", h_max.top()) << endl;
                res.push_back(h_max.top());
            }
        }

        cout << ord << ' ' << res.size() << '\n';
        for (int i = 0; i < res.size(); i++) {
            cout << res[i] << ' ';
            if (i < res.size() - 1 && (i + 1) % 10 == 0) {
                cout << '\n';
            }
        }
        cout << '\n';
    }
}