#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Sock {
    ll l, r, x;
};

struct Proc {
    vector<Sock> ss = vector<Sock>(1);
};

int n, q;

auto ps = vector<Proc>{};

auto mem = set<pair<ll, ll>>{};

void init() {
    mem.insert({0, numeric_limits<ll>::max() / 2});
    ps.resize(n + 1);
}

optional<pair<ll, ll>> get_mem(int L) {
    auto v = vector<pair<ll, ll>>(mem.begin(), mem.end());
    for (int i = 0; i < v.size(); i++) {
        auto comp = [](const pair<ll, ll> &p1, const pair<ll, ll> &p2) {
            if (p1.second - p1.first != p2.second - p2.first) {
                return p1.second - p1.first < p2.second - p2.first;
            } else {
                return tie(p1.first, p1.second) < tie(p2.first, p2.second);
            }
        };
        nth_element(v.begin(), v.begin() + i, v.end(), comp);
        auto [l, r] = v[i];
        if (l + L - 1 > r) {
            continue;
        } else {
            auto it = mem.lower_bound({l, r});
            assert(it->first == l);
            mem.erase(it);
            if (l + L <= r) { mem.insert({l + L, r}); }
            return pair{l, l + L - 1};
        }
    }
    return nullopt;
}

optional<ll> create(int p, int L) {
    auto &ss = ps[p].ss;
    auto opt = get_mem(L);
    if (opt) {
        auto [l, r] = opt.value();
        ss.push_back({l, r, -1});
        return l;
    }
    return nullopt;
}

ll deliver(int p) {
    ll ans = 0;
    auto &ss = ps[p].ss;
    for (int i = 1; i < ss.size(); i++) {
        auto &s = ss[i];
        if (s.x == -1) {
            s.x = s.l;
        } else {
            s.x += 1;
            if (s.x > s.r) { s.x = s.l; }
        }
        ans += s.x;
    }
    return ans;
}

void return_mem(ll l, ll r) {
    auto v = vector<pair<ll, ll>>{};

    auto it = mem.lower_bound({l, r});
    auto prv = mem.end();

    if (it != mem.begin()) { prv = prev(it); }

    if (prv != mem.end() && prv->second + 1 == l) {
        v.push_back({prv->first, prv->second});
        mem.erase(prv);
    }
    v.push_back({l, r});
    if (it != mem.end() && r + 1 == it->first) {
        v.push_back({it->first, it->second});
        mem.erase(it);
    }

    mem.insert({v.front().first, v.back().second});
}

void eliminate(int p, int I) {
    auto &ss = ps[p].ss;
    auto [l, r, _] = ss[I];
    return_mem(l, r);
    ss.erase(ss.begin() + I);
}

void solve() {
    for (int i = 0; i < q; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "new") {
            int p, L;
            cin >> p >> L;
            cout << create(p, L).value_or(-1) << '\n';
        } else if (cmd == "send") {
            int p;
            cin >> p;
            cout << deliver(p) << '\n';
        } else if (cmd == "delete") {
            int p, I;
            cin >> p >> I;
            eliminate(p, I);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("1.in", "r", stdin);

    cin >> n >> q;

    init();
    solve();
}