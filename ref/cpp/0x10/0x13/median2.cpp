#include <bits/stdc++.h>

using namespace std;

int p, id, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> p;
    for (int i = 1; i <= p; i++) {
        cin >> id >> m;
        list<pair<int, int>> lst;
        vector<list<pair<int, int>>::iterator> its;
        vector<int> res;
        for (int j = 0, t; j < m; j++) {
            cin >> t;
            lst.push_back({t, 0});
        }
        for (auto it = lst.begin(); it != lst.end(); it++) {
            its.push_back(it);
        }
        lst.sort();

        int idx = 0;
        for (auto it = lst.begin(); it != lst.end(); it++) {
            it->second = idx++;
        }

        auto mid = next(lst.begin(), (lst.size() - 1) >> 1);

        int left = (lst.size() - 1) >> 1;
        int right = (lst.size() - 1) >> 1;

        // left == right or left + 1 == right

        cout << id << ' ' << ((m + 1) >> 1) << '\n';

        for (int j = its.size() - 1; j >= 0; j--) {
            if (lst.size() & 1) {
                res.push_back(mid->first);
            }

            if (lst.size() == 1) {
                break;
            }

            // 1, 2 -> 1 -> ok
            // 1, 2 -> 2 -> ok

            auto it = its[j];
            if (it->second < mid->second) {
                lst.erase(it);
                left--;
            } else if (it->second > mid->second) {
                lst.erase(it);
                right--;
            } else {
                // 1, 2, 3, 4 -> 1, 3, 4: mid++; erase(it);
                // 1, 2, 3, 4, 5 -> 1, 2, 4, 5: mid--; erase(it);
                if (lst.size() & 1) {
                    mid--;
                    lst.erase(it);
                    left--;
                } else {
                    mid++;
                    lst.erase(it);
                    right--;
                }
            }
            if (left + 1 < right) {
                mid++;
                left++;
                right--;
            } else if (left > right) {
                mid--;
                left--;
                right++;
            }
        }

        reverse(res.begin(), res.end());

        for (int j = 0; j < res.size(); j++) {
            cout << res[j] << ' ';
            if ((j + 1) % 10 == 0) {
                cout << '\n';
            }
        }
        if (res.size() % 10 != 0) {
            cout << '\n';
        }
    }
}