#!/usr/bin/env python3

# 洛谷 P2949: Work Scheduling G
#
# 农夫约翰有很多工作要做！为了高效地经营农场，他必须从他所做的每一项工作中赚取利润，每项工作只需要一个时间单位。
#
# 他的工作日从时间0开始，总共有10^9个时间单位。他目前可以从N(1 ≤ N ≤ 10^5)项工作中选择要做的工作，这些工作被方便地编号为1到N。
#
# 虽然理论上他有可能完成所有N项工作，但实际上这是极不可能的，因为他在任何一个时间单位内只能完成一项工作，而截止日期通常会导致他无法完成所有任务。
#
# 第i项工作的截止时间为D_i(1 ≤ D_i ≤ 10^9)。
#
# 如果他在截止时间前完成第i项工作（如果当前时间为t，那么仅当D_i > t的时候他能做这个任务，完成后t → t + 1），他将获得P_i(1 ≤ P_i ≤10^9) 的利润。
#
# 给定一系列工作和截止日期，FJ能够获得的最大总利润是多少？答案可能无法容纳在32位整数中。
#
# example:
#
# input:
# 3
# 2 10
# 1 5
# 1 7
#
# output:
# 17

import sys

input = sys.stdin.readline

n = int(input())

d, p = ([0] * (n + 1) for _ in range(2))

for i in range(1, n + 1):
    d[i], p[i] = map(int, input().split())

o = sorted(range(1, n + 1), key=lambda i: d[i])

d = [d[0]] + [d[i] for i in o]
p = [p[0]] + [p[i] for i in o]

import heapq

h = []

for i in range(1, n + 1):
    heapq.heappush(h, (p[i], i))
    if len(h) > d[i]:
        heapq.heappop(h)

ans = 0

for t in h:
    ans += t[0]

print(ans)
