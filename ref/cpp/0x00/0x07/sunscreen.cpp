#include <bits/stdc++.h>

using namespace std;

struct Cow {
    int min_spf, max_spf;
};

struct Cream {
    int spf, cover;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    static Cow cows[2510];

    for (int i = 1; i <= n; i++) {
        cin >> cows[i].min_spf >> cows[i].max_spf;
    }

    static Cream creams[2510];

    for (int i = 1; i <= m; i++) {
        cin >> creams[i].spf >> creams[i].cover;
    }

    // ranges::sort(span(cows + 1, n), greater<>(), &Cow::min_spf);
    // ranges::sort(span(creams + 1, m), greater<>(), &Cream::spf);

    int cnt = 0;

    // sort(cows + 1, cows + n + 1, [&](auto x, auto y) { return x.min_spf > y.min_spf; });
    // sort(creams + 1, creams + m + 1, [&](auto x, auto y) { return x.spf > y.spf; });

    // for (int i = 1; i <= n; i++) {
    //     auto ms = cows[i].min_spf;
    //     auto Ms = cows[i].max_spf;

    //     auto idx = 1;
    //     for (; idx <= m && !(creams[idx].cover > 0 && ms <= creams[idx].spf && creams[idx].spf <= Ms); idx++) {}
    //     if (1 <= idx && idx <= m) {
    //         creams[idx].cover--;
    //         cnt++;
    //     }
    // }

    sort(cows + 1, cows + n + 1, [&](auto x, auto y) { return x.min_spf < y.min_spf; });
    sort(creams + 1, creams + m + 1, [&](auto x, auto y) { return x.spf < y.spf; });

    multiset<int> s;

    int j = 1;

    for (int i = 1; i <= m; i++) {
        int spf = creams[i].spf;
        int cover = creams[i].cover;

        for (; j <= n && cows[j].min_spf <= spf; j++) {
            s.insert(cows[j].max_spf);
        }

        while (cover--) {
            auto it = s.lower_bound(spf);
            if (it == s.end()) {
                break;
            }

            s.erase(it);
            cnt++;
        }
    }

    cout << cnt << endl;
}