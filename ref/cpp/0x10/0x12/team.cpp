#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int cnt = 0;
    while (cin >> n && n) {
        cout << "Scenario #" << ++cnt << endl;
        vector<vector<int>> groups(n);
        for (int i = 0; i < n; i++) {
            int m;
            cin >> m;
            groups[i].resize(m);
            for (int j = 0; j < m; j++) {
                cin >> groups[i][j];
            }
        }

        vector<string> cmds;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string cmd;
        while (getline(cin, cmd) && cmd != "STOP") {
            cmds.push_back(cmd);
        }

        // groups & cmds are ready

        deque<int> group_q;
        vector<deque<int>> qs(n);

        for (auto cmd : cmds) {
            if (cmd[0] == 'D') {
                if (!group_q.empty()) {
                    auto t = group_q.front();
                    if (!qs[t].empty()) {
                        cout << qs[t].front() << endl;
                        qs[t].pop_front();
                        if (qs[t].empty()) {
                            group_q.pop_front();
                        }
                    }
                }
            } else {
                auto t = stoi(cmd.substr(8));
                for (int i = 0; i < groups.size(); i++) {
                    // if (ranges::binary_search(groups[i], t)) {
                    if (binary_search(groups[i].begin(), groups[i].end(), t)) {
                        if (qs[i].empty()) {
                            group_q.push_back(i);
                        }
                        qs[i].push_back(t);
                        break;
                    }
                }
            }
        }
        cout << endl;
    }
}