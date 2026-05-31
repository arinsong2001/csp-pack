#!/usr/bin/env python3

import sys
# sys.setrecursionlimit()
# sys.stdin.readline(), str.strip(), str.split()

import math
# math.gcd(), math.lcm()
# math.perm(), math.comb()  # 指数级，规模不宜太大！
# comb_with_replacement = math.comb(n + k - 1, k)

import bisect
# bisect.bisect(), bisect.bisect_left(), bisect.bisect_right()
# bisect.insort(), bisect.insort_left(), bisect.insort_right()

import heapq
# heapq.heapify(), heapq.heapify_max()
# heapq.heappush(), heapq.heappush_max()
# heapq.heappop(), heapq.heappop_max()
#
# heapq的_max()系列来自python3.14+.
# 在此之前，可以用最小堆和取负值操作来模拟最大堆：
# heapq.heappush(h, -x)
# x = -heapq.heappop(h)

from collections import deque
# deque.append(), deque.popleft()  # 尾进头出
# deque.appendleft(), deque.pop()  # 头进尾出

from collections import defaultdict
# defaultdict(default_factory=None, /, [...]) --> dict with default factory

from collections import Counter
# Counter(iterable=None, /, **kwds)
# 数据规模较大时优先考虑defaultdict(int).

from itertools import count, cycle, repeat
# c = count(), next(c) -> 0, 1, 2, 3...
# cy = cycle('abc'), next(cy) -> 'a', 'b', 'c', 'a', 'b', 'c'...
# re = repeat('abc'), next(re) -> 'abc', 'abc', 'abc'...

from itertools import accumulate, pairwise
# arr_padded = [0] + arr
#
# pref = list(accumulate(arr_padded))
#
# def query(pref, l, r):
#     return pref[r] - pref[l - 1]
#
# diff = [arr_padded[0]] + [b - a for a, b in pairwise(arr_padded)]
#
# def operate(diff, l, r, v):
#     diff[l] += v
#     if r < len(diff) - 1:
#         diff[r + 1] -= v
#
# arr_operated = list(accumulate(diff))[1:]
#
# itertools.pairwise()来自python3.10+, 在此之前可以用以下方式代替：
# diff = [arr_padded[0]] + [b - a for a, b in zip(arr_padded, arr_padded[1:])]

from itertools import zip_longest
# zip(*iterables, strict=False) -> iterator of zip tuples  # strict来自python3.10+, 慎用。
# zip_longest(*iterables, fillvalue=None) -> iterator of zip tuples

from itertools import groupby
# groupby(iterable, key=None) -> iterator of (key, group) tuples
# group from (key, group) is also an iterator.
# 使用之前务必确保数据有序。

from itertools import chain
# chain(*iterables) -> iterator of elements from all the iterables
# chain.from_iterable(iterable) -> iterator of elements from iterables in the iterable
#
# [*row for row in mat]: 推导式中解包的特性来自python3.15+.
# 在此之前可以用以下方式代替：
# 1. list(chain.from_iterable(mat))
# 2. list(chain(*mat))

from itertools import product, permutations, combinations, combinations_with_replacement
# product(*iterables, repeat=1) -> iterator of cartesian product
# permutations(iterable, r=None) -> iterator of r-length permutations
# combinations(iterable, r) -> iterator of r-length combinations
# combinations_with_replacement(iterable, r) -> iterator of r-length combinations with replacement
# 指数级，规模不宜太大。

from functools import lru_cache
# lru装饰器，用于配合递归模拟简单dp.
#
# @lru_cache(maxsize=128)
# def fib(n):
#     if n < 2:
#         return n
#     return fib(n - 1) + fib(n - 2)
