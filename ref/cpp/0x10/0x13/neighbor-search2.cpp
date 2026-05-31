#include <bits/stdc++.h>

using namespace std;

int n;
pair<int, int> pr[100010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> pr[i].first;
        pr[i].second = i;
    }

    list<pair<int, int>> lst(pr + 1, pr + n + 1);

    auto it = lst.begin();
    vector<decay_t<decltype(it)>> its;
    while (it != lst.end()) {
        its.push_back(it);
        it++;
    }

    lst.sort();

    vector<string> res;

    auto show = [&](auto it, auto np) {
        stringstream ss;
        ss << abs(np->first - it->first) << ' ' << np->second << '\n';
        lst.erase(it);

        string s;
        getline(ss, s);
        res.push_back(s);
    };

    for (int i = its.size() - 1; i > 0; i--) {
        auto it = its[i];
        auto prv = it == lst.begin() ? lst.end() : prev(it);
        auto nxt = it == prev(lst.end()) ? lst.end() : next(it);
        if (prv == lst.end()) {
            show(it, nxt);
            continue;
        }
        if (nxt == lst.end()) {
            show(it, prv);
            continue;
        }
        if (abs(prv->first - it->first) <= abs(nxt->first - it->first)) {
            show(it, prv);
        } else {
            show(it, nxt);
        }
    }

    for (int i = res.size() - 1; i >= 0; i--) {
        cout << res[i] << endl;
    }
}