#include <bits/stdc++.h>

using namespace std;

struct Cow {
    int idx, st, ed, stall;
};

struct Stall {
    int idx, ed;
    bool operator>(const auto &other) const {
        return tie(ed, idx) > tie(other.ed, other.idx);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    static Cow cows[50010];

    for (int i = 1; i <= n; i++) {
        cows[i].idx = i;
        cin >> cows[i].st >> cows[i].ed;
    }

    priority_queue<Stall, vector<Stall>, greater<>> stalls;

    sort(cows + 1, cows + n + 1, [&](auto x, auto y) {
        return x.st < y.st;
    });

    int idx = 1;

    for (int i = 1; i <= n; i++) {
        if (!stalls.empty() && stalls.top().ed < cows[i].st) {
            auto s = stalls.top();
            stalls.pop();
            s.ed = cows[i].ed;
            stalls.push(s);

            cows[i].stall = s.idx;
        } else {
            auto s = Stall{idx++, cows[i].ed};
            stalls.push(s);

            cows[i].stall = s.idx;
        }
    }

    sort(cows + 1, cows + n + 1, [&](auto x, auto y) {
        return x.idx < y.idx;
    });

    cout << stalls.size() << endl;
    for (int i = 1; i <= n; i++) {
        cout << cows[i].stall << '\n';
    }
}