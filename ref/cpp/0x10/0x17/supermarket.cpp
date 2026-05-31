#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
int n;

struct Product {
    int p, d;
    bool operator<(const Product &other) const {
        return tie(d, p) < tie(other.d, other.p);
    }
    bool operator>(const Product &other) const {
        return tie(p, d) > tie(other.p, other.d);
    }
} prods[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            cin >> prods[i].p >> prods[i].d;
        }

        sort(prods, prods + n);

        priority_queue<Product, vector<Product>, greater<>> h;

        for (int i = 0; i < n; i++) {
            auto prod = prods[i];
            if (prod.d > h.size()) {
                h.push(prod);
            } else {
                assert(prod.d == h.size());
                if (prod.p > h.top().p) {
                    h.pop();
                    h.push(prod);
                }
            }
        }

        int ans = 0;
        while (!h.empty()) {
            ans += h.top().p;
            h.pop();
        }

        cout << ans << endl;
    }
}