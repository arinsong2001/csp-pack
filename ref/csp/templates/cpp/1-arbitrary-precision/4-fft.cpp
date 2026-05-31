#include <bits/stdc++.h>
#include <complex>

using namespace std;

using ll = long long;

typedef complex<double> C;

const double PI = acos(-1);

void fft(vector<C> &a, int invert) {
    int n = a.size();

    static vector<int> rev;
    static vector<C> roots{{0, 0}, {1, 0}};

    if ((int)rev.size() != n) {
        int k = __builtin_ctz(n);
        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
        }
    }

    if ((int)roots.size() < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            double angle = 2 * PI / (1 << (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots[2 * i] = roots[i];
                double ang = angle * (2 * i + 1 - (1 << k));
                roots[2 * i + 1] = C(cos(ang), sin(ang));
            }
            k++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    }

    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                C u = a[i + j];
                C v = a[i + j + len] * roots[len + j];
                a[i + j] = u + v;
                a[i + j + len] = u - v;
            }
        }
    }

    if (invert) {
        reverse(a.begin() + 1, a.end());
        for (C &x : a)
            x /= n;
    }
}

string mul(string a, string b) {
    vector<int> A, B;

    for (int i = a.size() - 1; i >= 0; i--)
        A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--)
        B.push_back(b[i] - '0');

    vector<C> fa(A.begin(), A.end()), fb(B.begin(), B.end());

    int n = 1;
    while (n < A.size() + B.size())
        n <<= 1;

    fa.resize(n);
    fb.resize(n);

    fft(fa, 0);
    fft(fb, 0);

    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];

    fft(fa, 1);

    vector<int> res(n);
    for (int i = 0; i < n; i++)
        res[i] = int(fa[i].real() + 0.5);

    // 处理进位
    for (int i = 0; i < n; i++) {
        if (res[i] >= 10) {
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
        }
    }

    // 去前导0
    while (res.size() > 1 && res.back() == 0)
        res.pop_back();

    string s;
    for (int i = res.size() - 1; i >= 0; i--)
        s += res[i] + '0';

    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;

    string ans = mul(a, b);
    cout << ans << "\n";
}
