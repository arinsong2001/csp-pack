#!/usr/bin/env python3

from collections import deque
from itertools import accumulate

# ----------------------------
# 单调栈
# ----------------------------


def next_greater(arr):
    res = [None] * len(arr)
    stack = []

    for i, x in enumerate(arr):
        while stack and arr[stack[-1]] < x:
            j = stack.pop()
            res[j] = x
        stack.append(i)

    return res


def next_less(arr):
    res = [None] * len(arr)
    stack = []

    for i, x in enumerate(arr):
        while stack and arr[stack[-1]] > x:
            j = stack.pop()
            res[j] = x
        stack.append(i)

    return res


# ----------------------------
# Largest Rectangle in Histogram
# ----------------------------


def largest_rectangle(heights):

    heights = heights + [float("-inf")]  # sentinel
    stack = []
    ans = 0

    for i, h in enumerate(heights):
        while stack and heights[stack[-1]] > h:
            idx = stack.pop()
            height = heights[idx]

            # when idx is popped:
            # next less: arr[i]
            # previous less: arr[stk[-1]]
            left = stack[-1] if stack else -1
            width = i - left - 1

            ans = max(ans, height * width)

        stack.append(i)

    return ans


# ----------------------------
# Sum of Subarray Minimums
# ----------------------------


def sum_of_min(arr, mod=10**9 + 7):

    arr = arr + [float("-inf")]
    stack = []
    res = 0

    for i, x in enumerate(arr):
        while stack and arr[stack[-1]] > x:
            idx = stack.pop()
            val = arr[idx]

            left = idx - (stack[-1] if stack else -1)
            right = i - idx

            res = (res + val * left * right) % mod

        stack.append(i)

    return res


# ----------------------------
# 单调队列
# Sliding Window Maximum
# ----------------------------


def sliding_max(nums, k):

    dq = deque()
    res = []

    for i, x in enumerate(nums):
        while dq and dq[0] <= i - k:
            dq.popleft()

        while dq and nums[dq[-1]] <= x:
            dq.pop()

        dq.append(i)

        if i >= k - 1:
            res.append(nums[dq[0]])

    return res


# ----------------------------
# Shortest Subarray ≥ K
# (Monotonic Queue + Prefix)
# ----------------------------


def shortest_subarray(nums, k):

    pref = list(accumulate(nums, initial=0))

    dq = deque()
    ans = float("inf")

    for i in range(len(pref)):
        while dq and pref[i] - pref[dq[0]] >= k:
            ans = min(ans, i - dq.popleft())

        while dq and pref[dq[-1]] >= pref[i]:
            dq.pop()

        dq.append(i)

    return ans if ans < float("inf") else -1
