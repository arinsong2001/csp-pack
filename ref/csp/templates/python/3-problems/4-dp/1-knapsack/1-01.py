#!/usr/bin/env python3

# 0-1背包
#
# 洛谷 P2871: [USACO07DEC] Charm Bracelet S
#
# example:
#
# input:
# 4 6
# 1 4
# 2 6
# 3 12
# 2 7
#
# output:
# 23

import sys

input = sys.stdin.readline

n, m = map(int, input().split())

items = [tuple(map(int, input().split())) for _ in range(n)]

dp = [0] * (m + 1)


# f[j] = max(f[j], f[j - w[i]] + d[i])
def resolve(its=items, f=dp, m=m):
    for w, d in its:
        for j in range(m, w - 1, -1):
            nd = f[j - w] + d
            if nd > f[j]:
                f[j] = nd
    return f[m]


print(resolve())

# 优化：
# 一次性读取所有数据
# 用tuple()替代generator()
# 避免iter套iter, eg: w, d = zip(*tuple(map(int, input().split()) for _ in range(n)))
# 用大小比较替换max()
# 用函数的默认参数避免全局变量查找
