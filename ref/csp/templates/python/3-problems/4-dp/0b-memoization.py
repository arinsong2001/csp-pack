#!/usr/bin/env python3

# 记忆化搜索
#
# 洛谷 P1048: 采药
#
# example:
#
# input:
# 70 3
# 71 100
# 69 1
# 1 2
#
# output:
# 3

import sys

input = sys.stdin.readline

T, M = map(int, input().split())

t, p = ([0] * (M + 1) for _ in range(2))

for i in range(1, M + 1):
    t[i], p[i] = map(int, input().split())

# t[i] -> 采药时间
# p[i] -> 草药价值

from functools import lru_cache

# ans = 0
#
#
# @lru_cache
# def dfs(pos, tleft, prof):
#     global ans
#     if tleft < 0:
#         return
#     if pos == M + 1:
#         ans = max(ans, prof)
#         return
#     dfs(pos + 1, tleft, prof)
#     dfs(pos + 1, tleft - t[pos], prof + p[pos])
#
#
# print(ans)


@lru_cache(None)  # 默认maxsize=128, 可能不够
def dfs(pos, tleft):  # 将要采pos处的草药时，还剩下tleft的时间
    if pos == M + 1:
        return 0

    # 不采pos的后续总profit
    res1 = dfs(pos + 1, tleft)

    # 采pos的后续总profit
    res2 = dfs(pos + 1, tleft - t[pos]) + p[pos] if tleft >= t[pos] else 0

    return max(res1, res2)


print(dfs(1, T))

# Q: 为什么新版本dfs()可以正确利用@lru_cache而旧版本不行？它们有什么本质区别？
#
# A:
# - 新版本是“函数式 DP”（返回值表示子问题最优解），旧版本是“枚举 + 全局变量更新”。
# - 而 @lru_cache 只对“函数返回值 = 子问题答案”这种结构有效。
#
# @lru_cache的本质：
# - 对于这样的一类递归：
# - 若：同样的参数，返回值一定相同。
# - 则：函数结果可以缓存。
# - 即：cache (f(state) = result)
#
# - @lru_cache(None)
# - def dfs(pos, tleft): -> (从pos开始，在剩余tleft的时间下，能获得的最大收益)
#
# - 可以看出，这是一个“完整子问题”，因此缓存成立。
