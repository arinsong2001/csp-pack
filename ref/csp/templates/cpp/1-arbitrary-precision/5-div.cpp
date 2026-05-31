#include <bits/stdc++.h>

using namespace std;

using ll = long long;

pair<string, ll> divmod(string a, ll b) {
    vector<int> A(a.size());
    for (int i = 0; i < A.size(); i++) {
        A[i] = a[i] - '0';
    }

    // assert(b > 0);

    vector<int> Q;
    ll r = 0;

    for (int i = 0; i < A.size(); i++) {
        r = r * 10 + A[i];
        Q.push_back(r / b);
        r %= b;
    }

    auto it = Q.begin();
    for (; it != Q.end() - 1 && *it == 0; it++) {}
    Q.erase(Q.begin(), it);

    string q(Q.size(), '\0');
    for (int i = 0; i < q.size(); i++) {
        q[i] = Q[i] + '0';
    }

    return pair{q, r};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a;
    ll b;
    cin >> a >> b;

    auto [q, r] = divmod(a, b);
    cout << q << "\n";
}
