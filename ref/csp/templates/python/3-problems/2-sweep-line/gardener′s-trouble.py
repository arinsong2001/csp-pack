#!/usr/bin/env python3

# 洛谷 P2163: 园丁的烦恼
#
# example:
#
# input:
# 3 1
# 0 0
# 0 1
# 1 0
# 0 0 1 1
#
# output:
# 3

import sys

# input() at a lower cost
input = sys.stdin.readline

# n points, m queries
n, m = map(int, input().split())

points = []
ys = []

# read points
for _ in range(n):
    x, y = map(int, input().split())
    points.append((x, y))
    ys.append(y)

events = []

# read queries
for i in range(m):
    x1, y1, x2, y2 = map(int, input().split())

    events.append((x2, y2, i, 1))
    events.append((x1 - 1, y2, i, -1))
    events.append((x2, y1 - 1, i, -1))
    events.append((x1 - 1, y1 - 1, i, 1))

    ys.append(y1 - 1)
    ys.append(y2)

# compress y coordinates
ys = sorted(set(ys))

# y -> y_idx
y_indices = {y: i + 1 for i, y in enumerate(ys)}  # 1-based

size = len(ys) + 1

# fenwick
bit = [0] * size


# operate_tree
def operate_tree(x, v):
    while x < size:
        bit[x] += v
        x += x & -x


# pref_of_tree
def pref_of_tree(x):
    s = 0
    while x > 0:
        s += bit[x]
        x -= x & -x
    return s


# sort points by x-coordinate for incremental insertion during the sweep
points.sort()

# sort events by x-coordinate so the sweep line processes them from left to right
events.sort()

ans = [0] * m

p = 0
for x, y, ev_idx, sign in events:
    # insert the y-coordinates of points whose x ≤ current sweep line into the BIT
    while p < n and points[p][0] <= x:
        operate_tree(y_indices[points[p][1]], 1)
        p += 1

    # ans[ev_idx] += sign * F(x, y)
    ans[ev_idx] += sign * pref_of_tree(y_indices[y])

print("\n".join(map(str, ans)))
