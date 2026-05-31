#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int n;

vector<int> stov(const string &s) {
    vector<int> res;
    res.reserve(s.size());
    for (int i = s.size() - 1; i >= 0; i--) {
        res.push_back(s[i] - '0');
    }
    return res;
}

string vtos(const vector<int> &v) {
    string s;
    for (int i = v.size() - 1; i >= 0; i--) {
        s += '0' + v[i];
    }
    return s;
}

vector<int> mul(const vector<int> &x, int y) {
    if (y == 0) {
        return {0};
    }
    assert(y > 0);
    ll t = 0;
    vector<int> res;
    for (int i = 0; i < x.size(); i++) {
        t += (ll)x[i] * y;
        res.push_back(t % 10);
        t /= 10;
    }
    while (t) {
        res.push_back(t % 10);
        t /= 10;
    }
    return res;
}

vector<int> primes;

void euler_sieve(int x) {
    vector<char> is_composite(x + 1);

    for (int i = 2; i <= x; i++) {
        if (!is_composite[i]) {
            primes.push_back(i);
        }

        for (auto p : primes) {
            if (i * p > x) {
                break;
            }
            is_composite[i * p] = true;
            if (i % p == 0) {
                break;
            }
        }
    }
}

unordered_map<ll, ll> fact(int x) {
    unordered_map<ll, ll> res;
    // for (int i = 2; i * i <= x; i++) {
    //     if (!binary_search(primes.begin(), primes.end(), i)) {
    //         continue;
    //     }
    //     ll t = i, c = 0;
    //     while (t <= x) {
    //         c += x / t;
    //         t *= i;
    //     }
    //     res[i] = c;
    // }
    for (auto p : primes) {
        if (p > x) {
            break;
        }
        ll t = p, c = 0;
        while (t <= x) {
            c += x / t;
            t *= p;
        }
        res[p] = c;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // static stack<int> s;
    // static vector<int> res;
    // int cnt = 0;

    // auto dfs = [&](auto &&self, int pos) {
    //     if (res.size() >= n) {
    //         cnt++;
    //         return;
    //     }

    //     if (!s.empty() && res.size() < n) {
    //         res.push_back(s.top());
    //         s.pop();
    //         self(self, pos);
    //         s.push(res.back());
    //         res.pop_back();
    //     }

    //     if (pos <= n) {
    //         s.push(pos);
    //         self(self, pos + 1);
    //         s.pop();
    //     }
    // };

    // dfs(dfs, 1);
    // cout << cnt << endl;

    // static ll s[60010];
    // s[0] = 1;
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= i; j++) {
    //         s[i] += s[j - 1] * s[i - j];
    //     }
    // }
    // cout << s[n] << endl;

    // static vector<vector<ll>> f(n + 1, vector<ll>(n + 1));

    // for (int j = 0; j <= n; j++) {
    //     f[0][j] = 1;
    // }

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 0; j <= n - i; j++) {
    //         if (i - 1 >= 0) {
    //             f[i][j] += f[i - 1][j + 1];
    //         }
    //         if (j - 1 >= 0) {
    //             f[i][j] += f[i][j - 1];
    //         }
    //     }
    // }

    // cout << f[n][0] << endl;

    // string s = "12345";

    // cout << format("{}", stov(s)) << endl;
    // cout << format("{}", vtos(mul(stov(s), 5))) << endl;
    // cout << format("{}", vtos(fact(20))) << endl;

    // 高精度 + 压位
    // 分解质因数 + 阶乘分解质因数

    // C_2n^n / (n + 1) == (2n)! / n! / n! / (n + 1)

    euler_sieve(2 * n);

    auto m1 = fact(2 * n);
    auto m2 = fact(n);
    auto m3 = fact(n + 1);

    for (auto [p, c] : m2) {
        m1[p] -= c;
    }

    for (auto [p, c] : m3) {
        m1[p] -= c;
    }

    vector<int> prod = {1};
    for (auto [p, c] : m1) {
        for (int i = 1; i <= c; i++) {
            prod = mul(prod, p);
        }
    }

    cout << vtos(prod) << endl;
}