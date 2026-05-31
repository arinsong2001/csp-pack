#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // ith person -> speaks read[i] lang
    vector<int> read(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> read[i];
    }

    int m;
    cin >> m;

    // ith movie -> with sound of sound[i] lang
    vector<int> sound(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> sound[i];
    }

    // ith movie -> with text of text[i] lang
    vector<int> text(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> text[i];
    }

    // merge
    vector<int> lang(read.begin() + 1, read.end());
    lang.insert(lang.end(), sound.begin() + 1, sound.end());
    lang.insert(lang.end(), text.begin() + 1, text.end());

    // sort & unique
    sort(lang.begin(), lang.end());
    lang.erase(unique(lang.begin(), lang.end()), lang.end());

    // lang: from the idx to the lang: lang[idx] -> the lang with the idx of idx
    // ids: from the lang to its idx: ids[the lang] -> the idx for the lang
    // lang.size() -> cnt of langs
    unordered_map<int, int> ids;
    for (int i = 0; i < lang.size(); i++) {
        ids[lang[i]] = i;
    }

    vector<int> cnt(lang.size());

    // the cnt of people who speak the lang with the idx of i
    for (int i = 1; i <= n; i++) {
        cnt[ids[read[i]]]++;
    }

    vector<tuple<int, int, int>> v;
    for (int i = 1; i <= m; i++) {
        // ids[sound[i]], ids[text[i]], i
        v.push_back({cnt[ids[sound[i]]], cnt[ids[text[i]]], i});
    }

    // for (auto [x, y, z] : v) {
    //     cout << x << ' ' << y << ' ' << z << endl;
    // }

    sort(v.begin(), v.end(), greater<>());
    auto [s, t, idx] = v[0];
    cout << idx << endl;
}