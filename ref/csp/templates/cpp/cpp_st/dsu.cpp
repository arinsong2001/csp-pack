#include <bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 1010;

int n; // arr's size (1-based)

// basics

int fa[N], sz[N];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y) {
    fa[find(x)] = find(y);
}

// 路径压缩 + 启发式合并

// 初始化
void init2(int n) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        sz[i] = 1;
    }
}

// 查找（路径压缩）
int find2(int x) {
    if (fa[x] != x)
        fa[x] = find2(fa[x]);
    return fa[x];
}

// 合并（按大小合并）
void unite2(int x, int y) {
    int fx = find2(x), fy = find2(y);

    if (fx == fy) {
        return;
    }

    if (sz[fx] > sz[fy]) {
        swap(fx, fy);
    }

    fa[fx] = fy;
    sz[fy] += sz[fx];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
