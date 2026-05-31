#!/usr/bin/env python3

# 洛谷 P1135: 奇怪的电梯
#
# example:
#
# input:
# 5 1 5
# 3 3 1 2 5
#
# output:
# 3

import sys

input = sys.stdin.readline

# N floors, from A to B
N, A, B = map(int, input().split())

K = [0] + list(map(int, input().split()))

dist = [-1] * (N + 1)
prev = [None] * (N + 1)

from collections import deque


def bfs(start=A):
    q = deque()

    dist[A] = 0
    q.append(start)

    while q:
        pos = q.popleft()
        if pos == B:
            curr = pos
            path = [curr]
            while curr != start:
                curr = prev[curr]
                path.append(curr)
            # print(list(reversed(path)))
            return dist[pos]

        if 1 <= (new_pos := pos + K[pos]) <= N and dist[new_pos] == -1:
            dist[new_pos] = dist[pos] + 1
            prev[new_pos] = pos
            q.append(new_pos)

        if 1 <= (new_pos := pos - K[pos]) <= N and dist[new_pos] == -1:
            dist[new_pos] = dist[pos] + 1
            prev[new_pos] = pos
            q.append(new_pos)

    return -1


print(bfs())
