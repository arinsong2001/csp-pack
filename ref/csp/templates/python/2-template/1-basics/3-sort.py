#!/usr/bin/env python3

from itertools import pairwise
import random


def bubble_sort(arr):
    res = arr[:]
    for i in range(len(res) - 1, 0, -1):
        for j in range(i):
            if res[j] > res[j + 1]:
                res[j], res[j + 1] = res[j + 1], res[j]
    return res


assert all(a <= b for a, b in pairwise(bubble_sort(random.choices(range(-1000, 1000), k=1000))))


def selection_sort(arr):
    res = arr[:]
    for i in range(len(res) - 1):
        index, minimal = i, res[i]
        for j in range(i + 1, len(res)):
            if res[j] < minimal:
                index, minimal = j, res[j]
        if index != i:
            res[i], res[index] = res[index], res[i]
    return res


assert all(a <= b for a, b in pairwise(selection_sort(random.choices(range(-1000, 1000), k=1000))))


# def insertion_sort(arr):
#     res = arr[:]
#     for i in range(1, len(res)):
#         tmp = res[i]
#         j = i - 1
#         while j >= 0 and res[j] > tmp:
#             res[j + 1] = res[j]
#             j -= 1
#         res[j + 1] = tmp
#     return res


import bisect


def insertion_sort(arr):
    res = []
    for n in arr:
        bisect.insort(res, n)
    return res


assert all(a <= b for a, b in pairwise(insertion_sort(random.choices(range(-1000, 1000), k=1000))))


def shell_sort(arr):
    res = arr[:]

    gap = 1
    while 3 * gap + 1 < len(res):
        gap = 3 * gap + 1

    while gap >= 1:
        for i in range(gap, len(res)):
            # tmp = res[i]
            # j = i - gap
            # while j >= 0 and res[j] > tmp:
            #     res[j + gap] = res[j]
            #     j -= gap
            # res[j + gap] = tmp

            # 本质依然是插入排序，每轮排序结束后后续仍可能有元素“插入”进来；
            # 反向的冒泡排序每轮结束后，左侧元素一定是全局最小。
            j = i - gap
            while j >= 0 and res[j] > res[j + gap]:
                res[j], res[j + gap] = res[j + gap], res[j]
                j -= gap

        gap //= 3

    return res


assert all(a <= b for a, b in pairwise(shell_sort(random.choices(range(-1000, 1000), k=1000))))


def merge_sort(arr):

    def helper(arr=arr):
        if len(arr) < 2:
            return arr
        mid = len(arr) // 2
        left, right = helper(arr[:mid]), helper(arr[mid:])
        merged = []
        i = j = 0
        while i < len(left) and j < len(right):
            if left[i] > right[j]:
                merged.append(right[j])
                j += 1
            else:
                merged.append(left[i])
                i += 1
        merged.extend(left[i:])
        merged.extend(right[j:])
        return merged

    res = helper()
    return res


assert all(a <= b for a, b in pairwise(merge_sort(random.choices(range(-1000, 1000), k=1000))))


def quick_sort(arr):

    def helper(arr=arr):
        if len(arr) < 2:
            return arr
        less = [x for x in arr[1:] if x <= arr[0]]
        greater = [x for x in arr[1:] if x > arr[0]]
        return helper(less) + [arr[0]] + helper(greater)

    res = helper()
    return res


assert all(a <= b for a, b in pairwise(quick_sort(random.choices(range(-1000, 1000), k=1000))))


def quick_sort3(arr):

    def helper(arr=arr):
        if len(arr) < 2:
            return arr
        pivot = random.choice(arr)
        less = [x for x in arr if x < pivot]
        equal = [x for x in arr if x == pivot]
        greater = [x for x in arr if x > pivot]
        return helper(less) + equal + helper(greater)

    res = helper()
    return res


assert all(a <= b for a, b in pairwise(quick_sort3(random.choices(range(-1000, 1000), k=1000))))


def quick_sort_in_place(arr):
    res = arr[:]

    def helper(arr=res, first=0, last=len(res) - 1):
        if first >= last:
            return
        pivot = arr[first]
        l, r = first, last
        while l < r:
            while l < r and arr[r] > pivot:
                r -= 1
            arr[l] = arr[r]
            while l < r and arr[l] <= pivot:
                l += 1
            arr[r] = arr[l]
        arr[l] = pivot
        helper(arr, first, l - 1)
        helper(arr, l + 1, last)

    helper()
    return res


assert all(a <= b for a, b in pairwise(quick_sort_in_place(random.choices(range(-1000, 1000), k=1000))))


def quick_sort_in_place3(arr):
    res = arr[:]

    def helper(arr=res, first=0, last=len(res) - 1):
        if first >= last:
            return

        # 随机选择pivot.
        index = random.randint(first, last)
        pivot = arr[index]
        arr[first], arr[index] = arr[index], arr[first]

        i = first + 1  # 当前正在处理的位置
        j = first  # less区间的右边界
        k = last + 1  # greater区间的左边界

        while i < k:
            if arr[i] < pivot:
                arr[i], arr[j + 1] = arr[j + 1], arr[i]
                i += 1
                j += 1
            elif arr[i] > pivot:
                arr[i], arr[k - 1] = arr[k - 1], arr[i]
                k -= 1
            else:
                i += 1

        # pivot存储在最左侧，故与less右边界的元素交换。
        arr[first], arr[j] = arr[j], arr[first]

        helper(arr, first, j - 1)
        helper(arr, k, last)

    helper()
    return res


assert all(a <= b for a, b in pairwise(quick_sort_in_place3(random.choices(range(-1000, 1000), k=1000))))

import heapq


def heap_sort(arr):
    h = arr[:]
    heapq.heapify(h)
    return [heapq.heappop(h) for _ in range(len(h))]


assert all(a <= b for a, b in pairwise(heap_sort(random.choices(range(-1000, 1000), k=1000))))

from itertools import accumulate


# def counting_sort(arr):
#     # 判空，防止max(arr)报错。
#     if not arr:
#         return []
#
#     # 计数，n in arr 要当作下标，所以cnt: 1-based.
#     cnt = [0] + [0] * max(arr)
#     for n in arr:
#         cnt[n] += 1
#
#     # 计算前缀和，完成：n in arr -> counter(n) -> new_index(1-based).
#     cnt = list(accumulate(cnt))
#
#     # 结果数组，和arr等长。
#     res = [0] * len(arr)
#
#     # 反向装填，用以保证排序的稳定性。
#     for n in reversed(arr):
#         # 注意：1-based -> 0-based -> index -= 1.
#         res[cnt[n] - 1] = n
#         cnt[n] -= 1
#
#     return res
#
#
# assert counting_sort(random.sample(range(1, 6), 5)) == list(range(1, 6))
#
#
# def counting_sort_with_minus(arr):
#     # tmp = [n - minimum for n in arr] if (minimum := min(arr)) < 0 else arr[:]
#     # return [n + minimum for n in counting_sort(tmp)] if minimum < 0 else counting_sort(tmp)
#     tmp = [n - (minimum := min(arr)) for n in arr]
#     return [n + minimum for n in counting_sort(tmp)]
#
#
# assert counting_sort_with_minus(random.sample(range(1, 6), 5)) == list(range(1, 6))


def counting_sort(arr):
    if not arr:
        return []

    # 确定计数范围。
    min_val = min(arr)
    max_val = max(arr)

    # 计数排序本质上是桶大小为1的桶排序。
    # 本质上，length: (max_val - min_val) // 1 + 1.
    length = max_val - min_val + 1

    # 计数。
    cnt = [0] * length
    for n in arr:
        cnt[n - min_val] += 1

    # 求前缀和。
    cnt_pref = list(accumulate(cnt))

    # 反向装填。
    res = [0] * len(arr)
    for n in reversed(arr):
        res[cnt_pref[n - min_val] - 1] = n
        cnt_pref[n - min_val] -= 1

    return res


assert all(a <= b for a, b in pairwise(counting_sort(random.choices(range(-1000, 1000), k=1000))))

# def radix_sort(arr):
#     max_len = len(str(max(arr)))
#     arr_with_str = [(n, f"{n:0{max_len}}") for n in arr]
#     for i in range(max_len):
#         arr_with_str.sort(key=lambda tup: tup[1][max_len - i - 1])
#     return [tup[0] for tup in arr_with_str]


def radix_sort(arr):
    if not arr:
        return []

    # 通过偏移处理负值。
    min_val = min(arr)
    res = [n - min_val for n in arr]

    # while循环条件：max_val // exp > 0.
    # exp = 1, 10, 100, ...
    max_val = max(res)
    exp = 1
    while max_val // exp > 0:
        # 通过 n // exp % 10 获取每个数位上的数字，作为index.
        # 故：index ranges from 0 to 9.
        cnt = [0] * 10
        for n in res:
            index = n // exp % 10
            cnt[index] += 1

        # 求前缀和。
        cnt_pref = list(accumulate(cnt))

        # 反向装填。
        for n in reversed(res[:]):  # 注意res[:]这个写法。
            index = n // exp % 10
            res[cnt_pref[index] - 1] = n
            cnt_pref[index] -= 1

        exp *= 10

    # 处理偏移，还原元素。
    return [n + min_val for n in res]


assert all(a <= b for a, b in pairwise(radix_sort(random.choices(range(-1000, 1000), k=1000))))


def bucket_sort(arr, bucket_size=5):
    if not arr:
        return []

    # 求min, max, 确定数据范围。
    min_val = min(arr)
    max_val = max(arr)

    # 创建 (max_val - min_val) // bucket_size + 1 个桶。
    bucket_count = (max_val - min_val) // bucket_size + 1
    buckets = [[] for _ in range(bucket_count)]

    # 按数值把数据分装进桶中。
    for n in arr:
        index = (n - min_val) // bucket_size
        buckets[index].append(n)

    # 排序并合并桶。
    res = []
    for bucket in buckets:
        res.extend(sorted(bucket))

    return res


assert all(a <= b for a, b in pairwise(bucket_sort(random.choices(range(-1000, 1000), k=1000))))
