#include <bits/stdc++.h>

using namespace std;

using ll = long long;

string mul(string a, string b) {
    vector<int> A(a.size()), B(b.size());

    for (int i = 0; i < A.size(); i++) {
        A[i] = a[i] - '0';
    }
    reverse(A.begin(), A.end());

    for (int i = 0; i < B.size(); i++) {
        B[i] = b[i] - '0';
    }
    reverse(B.begin(), B.end());

    vector<int> C(A.size() + B.size());

    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B.size(); j++) {
            C[i + j] += A[i] * B[j];
        }
    }

    int t = 0;
    for (int i = 0; i < C.size(); i++) {
        t += C[i];
        C[i] = t % 10;
        t /= 10;
    }

    while (C.size() > 1 && C.back() == 0) {
        C.pop_back();
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

    auto ans = mul(a, b);

    cout << ans << "\n";
}
