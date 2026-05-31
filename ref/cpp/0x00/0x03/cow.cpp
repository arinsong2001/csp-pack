#include <bits/stdc++.h>

using namespace std;

inline void hash_combine(size_t &seed, size_t value) {
    static const size_t random = mt19937(random_device{}())();
    static const size_t magic = (sqrt(5.0l) - 1) * (1ull << 63);
    seed ^= (value ^ random) + magic + (seed << 6) + (seed >> 2);
}

struct PairHash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
        size_t seed = 0;
        hash_combine(seed, hash<T1>{}(p.first));
        hash_combine(seed, hash<T2>{}(p.second));
        return seed;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, P, H, M;
    cin >> N >> P >> H >> M;

    vector<int> c(N + 2);

    unordered_set<pair<int, int>, PairHash> s;

    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        if (a > b) {
            swap(a, b);
        }
        if (s.count({a, b})) {
            continue;
        }
        s.insert({a, b});
        c[a + 1] -= 1;
        c[b] += 1;
    }

    partial_sum(c.begin(), c.end(), c.begin());

    for (int i = 1; i <= N; i++) {
        cout << c[i] + H << '\n';
    }
}