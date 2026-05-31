#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int n;
int arr[200010];

struct Comp {
    bool operator()(const int &x, const int &y) const {
        return arr[x] < arr[y];
    }
};

void show(const auto &arr) {
    for (const auto &x : arr) {
        cout << x << ' ';
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    vector<int> ids(n);
    iota(ids.begin(), ids.end(), 1);

    // ranges::sort(ids, {}, [&](auto x) { return arr[x]; });
    sort(ids.begin(), ids.end(), Comp{});

    // show(ids);

    vector<vector<int>>
        seqs;
    vector<int> seq;
    int curr = arr[0];

    for (int i = 0; i <= ids.size(); i++) {
        if (i == ids.size()) {
            seqs.push_back(seq);
            break;
        }
        if (arr[ids[i]] != curr) {
            seqs.push_back(seq);
            seq.clear();
            curr = arr[ids[i]];
        }
        seq.push_back(ids[i]);
    }

    // cout << format("{}", seqs) << endl;

    bool down = false;
    int cnt = 0;
    int min_val = numeric_limits<int>::min();
    int max_val = numeric_limits<int>::max();

    for (int i = 1; i < seqs.size(); i++) {
        auto [m, M] = minmax_element(seqs[i].begin(), seqs[i].end());
        if (down && *M > min_val || !down && *m < max_val) {
            down = !down;
            cnt += down ? 1 : 0;
        }
        min_val = *m;
        max_val = *M;
    }

    cout << cnt << endl;
}