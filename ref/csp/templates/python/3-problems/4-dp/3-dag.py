#!/usr/bin/env python3

# DAG上的DP
#
# 洛谷 UVA437: The Tower of Babylon
#
# example:
#
# input:
# 1
# 10 20 30
# 2
# 6 8 10
# 5 5 5
# 7
# 1 1 1
# 2 2 2
# 3 3 3
# 4 4 4
# 5 5 5
# 6 6 6
# 7 7 7
# 5
# 31 41 59
# 26 53 58
# 97 93 23
# 84 62 64
# 33 83 27
# 0
#
# output:
# Case 1: maximum height = 40
# Case 2: maximum height = 21
# Case 3: maximum height = 28
# Case 4: maximum height = 342

import sys

input = sys.stdin.readline

from collections import defaultdict
from collections import deque


def get_height(n, x, y, z):
    vertices = []
    for i in range(1, n + 1):
        # 每种立方体 -> 3个点
        vertices += [(x[i], y[i], z[i]), (x[i], z[i], y[i]), (y[i], z[i], x[i])]

    # 多源 -> 单源
    ground = (float("inf"), float("inf"), 0)
    vertices.append(ground)

    # 去重
    vertices = list(set(vertices))

    # 建图

    g = defaultdict(dict)

    indeg = defaultdict(int)  # in-degree

    for u in vertices:
        for v in vertices:
            if u == v:
                continue
            if u[0] > v[0] and u[1] > v[1]:
                g[u][v] = v[2]
                indeg[v] += 1

    # Kahn算法求拓扑排序

    q = deque()
    q.append(ground)

    topo = []

    while q:
        u = q.popleft()

        topo.append(u)

        for v in g[u]:
            indeg[v] -= 1
            if indeg[v] == 0:
                q.append(v)

    # 按拓扑序执行dp的状态转移

    dp = {}
    for u in vertices:
        dp[u] = 0

    for u in topo:
        for v in g[u]:
            dp[v] = max(dp[v], dp[u] + g[u][v])

    return max(dp.values())


res = []
while n := int(input()):
    x, y, z = ([0] * (n + 1) for _ in range(3))
    for i in range(1, n + 1):
        x[i], y[i], z[i] = sorted(map(int, input().split()))
    res.append(get_height(n, x, y, z))

for i in range(len(res)):
    print(f"Case {i + 1}: maximum height = {res[i]}")
