#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    static int f[5][20];

    int m = 4;
    int n = 12;

    for (int i = 3; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == 3) {
                f[i][j] = (1 << j) - 1;
            } else {
                if (j == 1) {
                    f[i][j] = 1;
                } else {
                    int min_val = 0x3f3f3f3f;
                    for (int k = 1; k < j; k++) {
                        min_val = min(min_val, 2 * f[i][k] + f[i - 1][j - k]);
                    }
                    f[i][j] = min_val;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << f[4][i] << '\n';
    }
}