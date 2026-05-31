#include <bits/stdc++.h>

using namespace std;

int n, k;
vector<int> arr;

struct Node {
    int val;
    bool alive;
};

list<Node> lst;

using iter = list<Node>::iterator;

struct Comp {
    bool operator()(const iter &x, const iter &y) {
        return x->val > y->val;
    }
};

priority_queue<iter, vector<iter>, Comp> h;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n >> k;

    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    adjacent_difference(arr.begin(), arr.end(), arr.begin());

    for (int i = 1; i < n; i++) {
        lst.push_back({arr[i], true});
    }

    lst.push_front({0x3f3f3f3f, true});
    lst.push_back({0x3f3f3f3f, true});

    for (auto it = next(lst.begin()); it != prev(lst.end()); it++) {
        h.push(it);
    }

    int ans = 0;

    for (int i = 0; i < k; i++) {
        auto t = h.top();
        h.pop();

        while (!t->alive) {
            t = h.top();
            h.pop();
        }

        ans += t->val;

        t->val = prev(t)->val + next(t)->val - t->val;

        prev(t)->alive = false;
        next(t)->alive = false;
        h.push(t);

        lst.splice(lst.end(), lst, prev(t));
        lst.splice(lst.end(), lst, next(t));
    }

    cout << ans << endl;
}