#!/usr/bin/env python3

import sys

input = sys.stdin.readline

# n -> sum of nums
# m -> count of nums
n, m = map(int, input().split())

path = []
res = []


def dfs(pos, rsrc, prev):
    if pos > m:
        if rsrc == 0:
            res.append(path[:])
        return

    for x in range(prev + 1, n + 1):
        if rsrc - x < 0:
            break

        k = m - pos
        min_sum = k * (2 * x + k + 1) // 2

        if rsrc - x - min_sum < 0:
            break

        path.append(x)
        dfs(pos + 1, rsrc - x, x)
        path.pop()


dfs(1, n, 0)
print(res)
