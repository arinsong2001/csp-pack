#!/usr/bin/env python3

# 洛谷 P1706: 全排列问题
#
# example:
#
# input:
# 3
#
# output:
#     1    2    3
#     1    3    2
#     2    1    3
#     2    3    1
#     3    1    2
#     3    2    1

import sys

input = sys.stdin.readline

n = int(input())

from itertools import permutations

for p in permutations(range(1, n + 1)):
    for x in p:
        print(f"{x:5}", end="")
    print()
