#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int n;

struct Flake {
    int a[10]; // 0-based is better for mod calc upon ids
    bool operator==(const Flake &other) const {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                bool eq;

                eq = true;
                for (int k = 0; k < 6; k++) {
                    if (a[(i + k) % 6] != other.a[(j + k) % 6]) {
                        eq = false;
                        break;
                    }
                }
                if (eq) {
                    return true;
                }

                eq = true;
                for (int k = 0; k < 6; k++) {
                    if (a[(i + k) % 6] != other.a[(j - k + 6) % 6]) {
                        eq = false;
                        break;
                    }
                }
                if (eq) {
                    return true;
                }
            }
        }
        return false;
    }
};

struct FlakeHash {
    size_t operator()(const Flake &flk) const {
        size_t sum = accumulate(flk.a, flk.a + 6, size_t(0));
        size_t prod = accumulate(flk.a, flk.a + 6, size_t(1), multiplies<>());
        return sum + prod;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    unordered_set<Flake, FlakeHash> s;
    for (int i = 0; i < n; i++) {
        auto flk = Flake{};
        for (int j = 0; j < 6; j++) {
            cin >> flk.a[j];
        }
        if (s.count(flk)) {
            cout << "Twin snowflakes found." << endl;
            return 0;
        } else {
            s.insert(flk);
        }
    }
    cout << "No two snowflakes are alike." << endl;
}