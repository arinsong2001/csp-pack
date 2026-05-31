#!/usr/bin/env python3

# 洛谷 P5490: 矩形面积并
#
# example:
#
# input:
# 2
# 100 100 200 200
# 150 150 250 255
#
# output:
# 18000

import sys

# input() at a lower cost
input = sys.stdin.readline

# n rectangles
n = int(input())

events = []
ys = []

# read rectangles
for _ in range(n):
    x1, y1, x2, y2 = map(int, input().split())
    events.append((x1, y1, y2, 1))  # 进入矩形
    events.append((x2, y1, y2, -1))  # 离开矩形
    ys.append(y1)
    ys.append(y2)

# sort events
events.sort()

# compress y coordinates
ys = sorted(set(ys))

# y -> y_idx
y_indices = {y: i for i, y in enumerate(ys)}

# count of y coordinates
size = len(ys)

# whether the entire interval is covered
cover = [0] * 4 * size

# covered length in the current interval
length = [0] * 4 * size


# cover[node] > 0 -> interval covered entirely -> length[node] = ys[r] - ys[l]
# cover[node] == 0:
# 1) l + 1 == r -> [l, r) is inseparable -> leaf node
# 2) l + 1 < r -> non-leaf node -> merge children
def push_up(node, l, r):
    if cover[node] > 0:
        length[node] = ys[r] - ys[l]
    elif l + 1 == r:
        length[node] = 0
    else:
        length[node] = length[node * 2] + length[node * 2 + 1]


# [l, r) ⊆ [ql, r) -> cover[node] += v(+1 or -1) -> push up the node
# otherwise -> update children -> push up the node
def update(node, l, r, ql, qr, v):
    if ql <= l and r <= qr:
        cover[node] += v
        push_up(node, l, r)
        return

    mid = (l + r) // 2

    if ql < mid:
        update(node * 2, l, mid, ql, qr, v)
    if qr > mid:
        update(node * 2 + 1, mid, r, ql, qr, v)

    push_up(node, l, r)


area = 0
prev_x = events[0][0]

for x, y1, y2, t in events:
    area += length[1] * (x - prev_x)
    # node[1] maintains interval [0, size - 1)
    update(1, 0, size - 1, y_indices[y1], y_indices[y2], t)
    prev_x = x

print(area)
