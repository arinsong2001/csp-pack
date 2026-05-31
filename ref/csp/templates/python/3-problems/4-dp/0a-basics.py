#!/usr/bin/env python3

# 动态规划基础
# 数字三角形 & LCS & LIS(LNDS)

tri = [
    [7],
    [3, 8],
    [8, 1, 0],
    [2, 7, 4, 4],
    [4, 5, 2, 6, 5],
]


def find_longest_path(tri):
    n = len(tri)

    f = [row[:] for row in tri]

    for i in range(n - 2, -1, -1):
        for j in range(i + 1):
            f[i][j] += max(f[i + 1][j], f[i + 1][j + 1])

    path = [7]
    j = 0
    for i in range(1, n):
        if f[i][j] < f[i][j + 1]:
            j += 1
        path.append(tri[i][j])

    return path


path = find_longest_path(tri)

assert path == [7, 3, 8, 7, 5]
assert sum(path) == 30


# LCS
def lcs(a, b):
    n, m = len(a), len(b)

    dp = [[0] * (m + 1) for _ in range(n + 1)]

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if a[i - 1] == b[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

    return dp[n][m]


assert lcs("abcde", "abce") == 4

import random

random.seed(0)

n = 10

arr = random.choices(range(100), k=n)


# LNDS -> O(n**2)
def lnds(arr):
    n = len(arr)
    dp = [1] * (n)
    for i in range(1, n):
        for j in range(i):
            if arr[j] <= arr[i]:
                dp[i] = max(dp[i], dp[j] + 1)
    return max(dp)


assert lnds(arr) == 4

# LNDS by memoization -> O(n**2)
from functools import lru_cache


def lnds_m(arr):
    n = len(arr)

    @lru_cache(None)
    def dfs(i):
        res = 1
        for j in range(i):
            if arr[i] >= arr[j]:
                res = max(res, dfs(j) + 1)
        return res

    return max(dfs(i) for i in range(n))


assert lnds_m(arr) == 4

import bisect


# LNDS -> O(nlogn)
def dp(arr):
    n = len(arr)
    arr_p = [0] + arr

    # d[k] -> 长度为k的不下降子序列末尾元素的最小值
    d = [0] * (n + 1)
    d[1] = arr_p[1]

    # 当前最长的不下降子序列的长度
    length = 1

    for i in range(2, n + 1):
        # 新进来的a[i] > d[len]
        if arr_p[i] > d[length]:
            d[length + 1] = arr_p[i]
            length += 1
        # 新进来的a[i] <= d[len]
        else:
            # 如果是上升子序列(LIS), 用bisect_left()
            idx = bisect.bisect_right(d, arr_p[i], 1, length + 1)
            d[idx] = arr_p[i]

    return length


assert dp(arr) == 4
