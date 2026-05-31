#!/usr/bin/env python3

# 多重背包
#
# 洛谷 P1776: 宝物筛选
#
# example:
#
# input:
# 4 20
# 3 9 3
# 5 9 1
# 9 4 2
# 8 1 3
#
# output:
# 47

import sys

input = sys.stdin.readline

n, W = map(int, input().split())

v, w, m = [[0] * (n + 1) for _ in range(3)]

for i in range(1, n + 1):
    v[i], w[i], m[i] = map(int, input().split())

# 朴素

# f = [0] * (W + 1)
#
# for i in range(1, n + 1):
#     for j in range(W, w[i] - 1, -1):
#         for k in range(1, m[i] + 1):
#             if k * w[i] > j:
#                 break
#             f[j] = max(f[j], f[j - k * w[i]] + k * v[i])
#
# print(f[W])

# 二进制分组优化

# f = [0] * (W + 1)
#
# for i in range(1, n + 1):
#     count = 1
#     while m[i] >= count:
#         vi = v[i] * count
#         wi = w[i] * count
#         for j in range(W, wi - 1, -1):
#             f[j] = max(f[j], f[j - wi] + vi)
#         m[i] -= count
#         count <<= 1
#     if m[i] > 0:
#         vi = v[i] * m[i]
#         wi = w[i] * m[i]
#         for j in range(W, wi - 1, -1):
#             f[j] = max(f[j], f[j - wi] + vi)
#
# print(f[W])

# 单调队列优化
#
# f[j] = max(f[j - k * w[i]] + k * v[i] for k in range(m[i] + 1))
# j = r + t * w[i]
# f[r + t * w[i]] = max(f[r + (t - k) * w[i]] + k * v[i] for k in range(m[i] + 1))
# f[r + t * w[i]] = max(f[r + (t - k) * w[i]] - (t - k) * v[i] + t * v[i] for k in range(m[i] + 1))
# def g(x): f[r + x * w[i]] - x * v[i]
# -> f[r + t * w[i]] = max(g(x) + t * v[i] for x in range(t - m[i], t + 1))

f = [0] * (W + 1)

from collections import deque

for i in range(1, n + 1):
    wi = w[i]
    vi = v[i]
    mi = m[i]

    for r in range(wi):
        q = deque()

        for t in range((W - r) // wi + 1):
            j = r + t * wi
            val = f[j] - t * vi

            while q and q[0][0] < t - mi:
                q.popleft()

            while q and q[-1][1] < val:
                q.pop()

            q.append((t, val))

            f[j] = q[0][1] + t * vi

print(f[W])
