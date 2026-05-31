#include <bits/stdc++.h>

using namespace std;

using ll = long long;

string sub(string a, string b) {
    bool minus = false;
    if (a.size() < b.size() || a.size() == b.size() && a < b) {
        minus = true;
        swap(a, b);
    }

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

    for (int i = 0; i < A.size(); i++) {
        t = A[i] - t;
        if (i < B.size()) {
            t -= B[i];
        }

        C.push_back((t + 10) % 10);

        t = t < 0 ? 1 : 0;
    }

    while (C.size() > 1 && C.back() == 0) {
        C.pop_back();
    }
    reverse(C.begin(), C.end());

    string c(C.size(), '\0');
    for (int i = 0; i < c.size(); i++) {
        c[i] = C[i] + '0';
    }

    return minus ? "-" + c : c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;

    auto ans = sub(a, b);
    cout << ans << "\n";
}
