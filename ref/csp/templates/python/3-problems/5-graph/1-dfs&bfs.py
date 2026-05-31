#!/usr/bin/env python3

from collections import defaultdict

graph = defaultdict(dict)

graph["start"]["a"] = 6
graph["start"]["b"] = 2
graph["a"]["end"] = 1
graph["b"]["a"] = 3
graph["b"]["end"] = 5


def dfs(graph=graph, u="start", end="end", vis=None):
    if vis is None:
        vis = set()

    vis.add(u)

    if u == end:
        return True

    for v in graph[u]:
        if v not in vis:
            if dfs(graph, v, end, vis):
                return True

    return False


assert dfs() is True

from collections import deque


def dfs_with_stack(graph=graph, start="start", end="end"):
    q = deque()
    q.append(start)

    vis = set()
    vis.add(start)

    while q:
        u = q.pop()

        if u == end:
            return True

        for v in graph[u]:
            if v not in vis:
                vis.add(v)
                q.append(v)

    return False


assert dfs_with_stack() is True


def bfs(graph=graph, start="start", end="end"):
    q = deque()
    q.append(start)

    vis = set()
    vis.add(start)

    while q:
        u = q.popleft()

        if u == end:
            return True

        for v in graph[u]:
            if v not in vis:
                vis.add(v)
                q.append(v)

    return False


assert bfs() is True

graph2 = defaultdict(dict)

graph2["start"]["a"] = 1
graph2["start"]["b"] = 0
graph2["a"]["end"] = 0
graph2["b"]["a"] = 1
graph2["b"]["end"] = 1


def bfs_with_deque(graph=graph2, start="start", end="end"):
    dq = deque()
    dq.append(start)

    cs = {start: 0}

    while dq:
        u = dq.popleft()

        # 第一次到达end时不一定是最短路径！
        # if u == end:
        #     break

        for v, w in graph[u].items():
            nc = cs[u] + w

            if nc < cs.get(v, float("inf")):
                cs[v] = nc

                if w == 0:
                    dq.appendleft(v)
                elif w == 1:
                    dq.append(v)
                else:
                    raise Exception("error!")

    return end in cs


assert bfs_with_deque() is True

import heapq


def bfs_with_heap(graph=graph, start="start", end="end"):
    h = [(0, start)]
    vis = set()

    cs = {start: 0}
    ps = {}

    while h:
        c, u = heapq.heappop(h)

        if u in vis:
            continue
        vis.add(u)

        if u == end:
            break

        for v, w in graph[u].items():
            nc = c + w
            if nc < cs.get(v, float("inf")):
                heapq.heappush(h, (nc, v))
                cs[v] = nc
                ps[v] = u

    if end in ps:
        path = []
        curr = end
        while curr in ps:
            path.append(f"({ps[curr]} -> {curr})")
            curr = ps[curr]
        return path

    if start == end:
        raise Exception("start is end!")

    raise Exception("unreachable!")


assert " ".join(reversed(bfs_with_heap())) == "(start -> b) (b -> a) (a -> end)"
