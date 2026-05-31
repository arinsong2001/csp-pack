#include <bits/stdc++.h>

using namespace std;

using ll = long long;

string add(string a, string b) {
    vector<int> A(a.size()), B(b.size());

    for (int i = 0; i < A.size(); i++) {
        A[i] = a[i] - '0';
    }
    reverse(A.begin(), A.end());

    for (int i = 0; i < B.size(); i++) {
        B[i] = b[i] - '0';
    }
    reverse(B.begin(), B.end());

    vector<int> C;
    int t = 0;

    for (int i = 0; i < A.size() || i < B.size() || t; i++) {
        if (i < A.size()) {
            t += A[i];
        }
        if (i < B.size()) {
            t += B[i];
        }

        C.push_back(t % 10);
        t /= 10;
    }

    reverse(C.begin(), C.end());

    string c(C.size(), '\0');
    for (int i = 0; i < c.size(); i++) {
        c[i] = C[i] + '0';
    }

    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;

    auto ans = add(a, b);
    cout << ans << "\n";
}
