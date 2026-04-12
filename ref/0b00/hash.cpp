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
        size_t h1 = hash<T1>{}(p.first);
        size_t h2 = hash<T2>{}(p.second);
        size_t seed = 0;
        hash_combine(seed, h1);
        hash_combine(seed, h2);
        return seed;
    }
};

struct TupleHash {
    template <class... T>
    size_t operator()(const tuple<T...> &t) const {
        size_t seed = 0;
        auto f = [&](const auto &...args) {
            (hash_combine(seed, hash<decay_t<decltype(args)>>{}(args)), ...);
        };
        apply(f, t);
        return seed;
    }
};
