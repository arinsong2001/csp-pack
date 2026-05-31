#!/usr/bin/env python3

import sys

sys.setrecursionlimit(10**8)
print(f"{sys.getrecursionlimit()=!r}")

input = sys.stdin.readline

n = int(input())
print(f"{n=!r}")

nums = list(map(int, input().split()))
print(f"{nums=!r}")

n, m = map(int, input().split())
print(f"{n, m=!r}")

nums2 = [list(map(int, input().split())) for _ in range(n)]
print(f"{nums2=!r}")

import math

print(f"{math.gcd(25, 7)=!r}")
print(f"{math.lcm(25, 7)=!r}")

import bisect

arr = list(range(1, 6))
print(f"{bisect.bisect(arr, 3)=!r}")
print(f"{bisect.bisect_left(arr, 3)=!r}")

bisect.insort(arr, 3)
bisect.insort_left(arr, 3)
print(f"{arr=!r}")

arr = list(set(arr))
print(f"{arr=!r}")

import heapq
import random

random.shuffle(arr)
print(f"{arr=!r}")

h = arr[:]
heapq.heapify(h)
print(f"{h=!r}")

arr = [heapq.heappop(h) for _ in range(len(h))]
print(f"{arr=!r}")

from collections import deque

dq = deque(arr)
print(f"{dq=!r}")

dq.append(dq.popleft())
print(f"{dq=!r}")

dq.rotate(1)
print(f"{dq=!r}")

from collections import defaultdict

graph = defaultdict(dict)

graph["start"]["a"] = 6
graph["start"]["b"] = 2
graph["a"]["end"] = 1
graph["b"]["a"] = 3
graph["b"]["end"] = 5


def dijkstra(graph=graph, start="start", end="end"):
    dist = {start: 0}

    h = [(0, start)]

    # vis = set()

    pars = {}

    while h:
        d, u = heapq.heappop(h)

        # if u in vis:
        #     continue
        # vis.add(u)

        if dist.get(u, float("inf")) < d:
            continue

        if u == end:
            break

        for v, w in graph[u].items():
            nd = d + w
            if nd < dist.get(v, float("inf")):
                heapq.heappush(h, (nd, v))
                dist[v] = nd
                pars[v] = u

    if end not in dist:
        return "unreachable!"

    path = [end]
    curr = end

    while curr in pars:
        path.append(pars[curr])
        curr = pars[curr]

    return " -> ".join(reversed(path))


print(f"{dijkstra()=!r}")

from collections import Counter

counter = Counter("ababaca")
print(f"{counter=!r}")

from itertools import count, cycle, repeat

its = count(), cycle("abc"), repeat("abc")
print(f"{[[next(it) for it in its] for _ in range(5)]=!r}")

from itertools import accumulate, pairwise

arr_p = [0] + arr
print(f"{arr_p=!r}")


# def prefix(arr_p):
#     return (lambda s=0: [s := s + x for x in arr_p])()


def prefix(arr_p):
    return list(accumulate(arr_p))


def query(pref, l, r):
    return pref[r] - pref[l - 1]


# def differ(arr_p):
#     return [arr_p[0]] + [b - a for a, b in zip(arr_p, arr_p[1:])]


def differ(arr_p):
    return [arr_p[0]] + [b - a for a, b in pairwise(arr_p)]


def operate(diff, l, r, v):
    diff[l] += v
    if r + 1 < len(diff):
        diff[r + 1] -= v


pref = prefix(arr_p)
print(f"{pref=!r}")

diff = differ(arr_p)
print(f"{diff=!r}")

print(f"{query(pref, 2, 4)=!r}")

operate(diff, 2, 4, 1)
print(f"{prefix(diff)[1:]=!r}")

operate(diff, 2, 4, -1)
print(f"{prefix(diff)[1:]=!r}")

mat = [list(range(1 + 5 * x, 6 + 5 * x)) for x in range(5)]
mat_p = [[0] + [0] * (len(mat[0]))] + [[0] + row for row in mat]
print(f"{mat_p=!r}")


# def prefix2(mat_p):
#     pref_row = [(lambda s=0: [s := s + x for x in row])() for row in mat_p]
#     pref_col = [(lambda s=0: [s := s + x for x in col])() for col in zip(*pref_row)]
#     return [list(row) for row in zip(*pref_col)]


def prefix2(mat_p):
    pref_row = [list(accumulate(row)) for row in mat_p]
    pref_col = [list(accumulate(col)) for col in zip(*pref_row)]
    return [list(row) for row in zip(*pref_col)]


def query2(pref2, i1, j1, i2, j2):
    return pref2[i2][j2] - pref2[i1 - 1][j2] - pref2[i2][j1 - 1] + pref2[i1 - 1][j1 - 1]


# def differ2(mat_p):
#     diff_row = [[row[0]] + [b - a for a, b in zip(row, row[1:])] for row in mat_p]
#     diff_col = [[col[0]] + [b - a for a, b in zip(col, col[1:])] for col in zip(*diff_row)]
#     return [list(row) for row in zip(*diff_col)]


def differ2(mat_p):
    diff_row = [[row[0]] + [b - a for a, b in pairwise(row)] for row in mat_p]
    diff_col = [[col[0]] + [b - a for a, b in pairwise(col)] for col in zip(*diff_row)]
    return [list(row) for row in zip(*diff_col)]


# def operate2(diff2, i1, j1, i2, j2, v):
#     diff2[i1][j1] += v
#     if i2 + 1 < len(diff2):
#         diff2[i2 + 1][j1] -= v
#     if j2 + 1 < len(diff2[0]):
#         diff2[i1][j2 + 1] -= v
#     if i2 + 1 < len(diff2) and j2 + 1 < len(diff[0]):
#         diff2[i2 + 1][j2 + 1] += v


def operate2(diff2, i1, j1, i2, j2, v):
    for i, si in ((i1, 1), (i2 + 1, -1)):
        if not i < len(diff2):
            continue
        for j, sj in ((j1, 1), (j2 + 1, -1)):
            if not j < len(diff2[0]):
                continue
            diff2[i][j] += v * si * sj


pref2 = prefix2(mat_p)
print(f"{pref2=!r}")

diff2 = differ2(mat_p)
print(f"{diff2=!r}")

print(f"{query2(pref2, 2, 2, 4, 4)=!r}")

operate2(diff2, 2, 2, 4, 4, 1)
print(f"{[row[1:] for row in prefix2(diff2)[1:]]=!r}")

operate2(diff2, 2, 2, 4, 4, -1)
print(f"{[row[1:] for row in prefix2(diff2)[1:]]=!r}")

from itertools import zip_longest

print(f"{[(a, b) for a, b in zip_longest(arr_p, arr_p[1:])]=!r}")

from itertools import groupby

print(f"{[(k, list(g)) for k, g in groupby(sorted("ababaca"))]=!r}")

from itertools import chain

print(f"{hex(int("".join(map(str, chain(*mat))), 10))=!r}")

from itertools import product, permutations, combinations, combinations_with_replacement

print(f"{list(product([1, 2, 3], ['a', 'b', 'c']))=!r}")
print(f"{list(permutations([1, 2, 3]))=!r}")
print(f"{list(combinations([1, 2, 3], r=2))=!r}")
print(f"{list(combinations_with_replacement([1, 2, 3], r=2))=!r}")

from functools import lru_cache


@lru_cache
def fib(n):
    if n < 2:
        return n
    return fib(n - 1) + fib(n - 2)


print(f"{fib(40)=!r}")
