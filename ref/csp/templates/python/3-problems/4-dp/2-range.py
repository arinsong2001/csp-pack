#!/usr/bin/env python3

# 区间DP
#
# LOJ P10147: NOI1995 石子合并
#
# example:
#
# input:
# 4
# 4 5 9 4
#
# output:
# 43
# 54

import sys

input = sys.stdin.readline

n = int(input())

a = list(map(int, input().split()))

pref = (lambda s=0: [s := s + x for x in [0] + a + a])()


def seek_min(n=n, pref=pref):
    f = [[float("inf")] * (2 * n) for _ in range(2 * n)]

    for i in range(2 * n):
        f[i][i] = 0

    for length in range(2, n + 1):
        for i in range(1, 2 * n - length + 1):  # -> 1 to 2 * n - length
            # i_max + length - 1 == 2 * n - 1 -> i_max == 2 * n - length
            j = i + length - 1  # -> i + length - 1 to 2 * n - 1
            for k in range(i, j):
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + pref[j] - pref[i - 1])

    return min(f[i][i + n - 1] for i in range(1, n + 1))


def seek_max(n=n, pref=pref):
    f = [[0] * (2 * n) for _ in range(2 * n)]

    for length in range(2, n + 1):
        for i in range(1, 2 * n - length + 1):  # -> 1 to 2 * n - length
            # i_max + length - 1 == 2 * n - 1 -> i_max == 2 * n - length
            j = i + length - 1  # -> i + length - 1 to 2 * n - 1
            for k in range(i, j):
                f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + pref[j] - pref[i - 1])

    return max(f[i][i + n - 1] for i in range(1, n + 1))


print(seek_min())
print(seek_max())
