#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // vector<string> qs;
    // for (int i = 0; i < q; i++) {
    //     string s;
    //     getline(cin, s);
    //     qs.push_back(s);
    // }

    // ranges::for_each(qs, [&](auto x) { cout << x << endl; });

    stack<int> f, b;
    stack<int> pref;
    vector<int> max_p;

    for (int i = 0; i < q; i++) {
        int x, k;
        string s;
        getline(cin, s);
        switch (s[0]) {
        case 'I':
            x = stoi(s.substr(2));
            f.push(x);
            if (pref.empty()) {
                pref.push(x);
            } else {
                pref.push(pref.top() + x);
            }
            if (max_p.empty()) {
                max_p.push_back(x);
            } else {
                max_p.push_back(max(max_p.back(), pref.top()));
            }
            break;
        case 'D':
            if (f.empty()) {
                break;
            }
            f.pop();
            pref.pop();
            max_p.pop_back();
            break;
        case 'L':
            if (f.empty()) {
                break;
            }
            b.push(f.top());
            f.pop();
            pref.pop();
            max_p.pop_back();
            break;
        case 'R':
            if (b.empty()) {
                break;
            }
            x = b.top();
            b.pop();
            f.push(x);
            if (pref.empty()) {
                pref.push(x);
            } else {
                pref.push(pref.top() + x);
            }
            if (max_p.empty()) {
                max_p.push_back(x);
            } else {
                max_p.push_back(max(max_p.back(), pref.top()));
            }
            break;
        case 'Q':
            k = stoi(s.substr(2));
            cout << max_p[k - 1] << '\n';
            break;
        }
    }
}