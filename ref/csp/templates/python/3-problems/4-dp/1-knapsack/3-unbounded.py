#!/usr/bin/env python3

# 完全背包
#
# 洛谷 P1616: 疯狂的采药
#
# example:
#
# input:
# 70 3
# 71 100
# 69 1
# 1 2
#
# output:
# 140

import sys

input = sys.stdin.readline

t, m = map(int, input().split())

a, b = ([0] * (m + 1) for _ in range(2))
for i in range(1, m + 1):
    a[i], b[i] = map(int, input().split())

f = [0] * (t + 1)

for i in range(1, m + 1):
    for j in range(a[i], t + 1):
        nt = f[j - a[i]] + b[i]
        if nt > f[j]:
            f[j] = nt

print(f[t])
