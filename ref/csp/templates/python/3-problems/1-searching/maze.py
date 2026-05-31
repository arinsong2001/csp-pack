#!/usr/bin/env python3

# 洛谷 B3625: 迷宫寻路
#
# example:
#
# input:
# 3 5
# .##.#
# .#...
# ...#.
#
# output:
# Yes

import sys

sys.setrecursionlimit(10**8)

input = sys.stdin.readline

n, m = map(int, input().split())

maze = []
for _ in range(n):
    maze.append(list(input().rstrip()))

maze_p = [[" "] + [" "] * len(maze[0])] + [[" "] + row for row in maze]

vis = [[False] * len(maze_p[0]) for _ in range(len(maze_p))]


def dfs(i=1, j=1):
    if not (1 <= i <= n and 1 <= j <= m and maze_p[i][j] == ".") or vis[i][j]:
        return False

    if i == n and j == m:
        return True

    vis[i][j] = True

    return dfs(i, j - 1) or dfs(i - 1, j) or dfs(i, j + 1) or dfs(i + 1, j)


from collections import deque


def is_legal(i, j):
    if not (1 <= i <= n and 1 <= j <= m and maze_p[i][j] == ".") or vis[i][j]:
        return False
    return True


def bfs(start=(1, 1)):
    q = deque()

    vis[1][1] = True
    q.append(start)

    while q:
        i, j = q.popleft()

        if i == n and j == m:
            return True

        if is_legal(i - 1, j):
            vis[i - 1][j] = True
            q.append((i - 1, j))
        if is_legal(i + 1, j):
            vis[i + 1][j] = True
            q.append((i + 1, j))
        if is_legal(i, j - 1):
            vis[i][j - 1] = True
            q.append((i, j - 1))
        if is_legal(i, j + 1):
            vis[i][j + 1] = True
            q.append((i, j + 1))

    return False


# print("Yes" if dfs() else "No")
print("Yes" if bfs() else "No")
