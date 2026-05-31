#!/usr/bin/env python3

# === test start ===
arr = list(range(1, 6))
arr_p = [0] + arr
# === test end ===

# 单点操作，区间查询


def lb(x):
    return x & -x


# O(n)建树
# def init_tree(arr_p):
#     c = [0] * len(arr_p)
#     for i in range(1, len(c)):
#         c[i] += arr_p[i]
#         j = i + lb(i)
#         if j < len(c):
#             c[j] += c[i]
#     return c


# def init_tree(arr_p):
#     c = arr_p[:]
#     for i in range(1, len(c)):
#         j = i + lb(i)
#         if j < len(c):
#             c[j] += c[i]
#     return c


from itertools import accumulate


def prefix(arr_p):
    return list(accumulate(arr_p))


def init_tree(arr_p):
    pref = prefix(arr_p)
    c = [0] * len(arr_p)
    for i in range(1, len(c)):
        c[i] = pref[i] - pref[i - lb(i)]
    return c


# 单点操作
def operate_tree(c, x, v):
    while x < len(c):
        c[x] += v
        x += lb(x)


# 求pref[x]
def pref_of_tree(c, x):
    res = 0
    while x > 0:
        res += c[x]
        x -= lb(x)
    return res


# 区间查询
def query_tree(c, l, r):
    return pref_of_tree(c, r) - pref_of_tree(c, l - 1)


# === test start ===
c_a = init_tree(arr_p)

operate_tree(c_a, 3, 1)
assert [query_tree(c_a, x, x) for x in range(1, len(c_a))] == [1, 2, 4, 4, 5]

operate_tree(c_a, 3, -1)
assert [query_tree(c_a, x, x) for x in range(1, len(c_a))] == [1, 2, 3, 4, 5]
# === test end ===

# 区间操作，单点查询

from itertools import pairwise


def differ(arr_p):
    return [0] + [b - a for a, b in pairwise(arr_p)]


def init_tree_interval(arr_p):
    return init_tree(differ(arr_p))


def operate_tree_interval(c, l, r, v):
    operate_tree(c, l, v)
    if r + 1 < len(c):
        operate_tree(c, r + 1, -v)


def query_tree_interval(c, x):
    return pref_of_tree(c, x)


# === test start ===
c_d = init_tree_interval(arr_p)

operate_tree_interval(c_d, 2, 4, 1)
assert [query_tree_interval(c_d, x) for x in range(1, len(c_d))] == [1, 3, 4, 5, 5]

operate_tree_interval(c_d, 2, 4, -1)
assert [query_tree_interval(c_d, x) for x in range(1, len(c_d))] == [1, 2, 3, 4, 5]
# === test end ===

# 区间操作，区间查询


def init_tree_intervals(arr_p):
    diff = differ(arr_p)
    c1 = init_tree(diff)
    c2 = init_tree([e * i for i, e in enumerate(diff)])
    return c1, c2


def operate_tree_intervals(c1, c2, l, r, v):
    # operate_tree(c1, l, v)
    # if r + 1 < len(c1):
    #     operate_tree(c1, r + 1, -v)
    # operate_tree(c2, l, v * l)
    # if r + 1 < len(c2):
    #     operate_tree(c2, r + 1, -v * (r + 1))

    def helper(x, v):
        operate_tree(c1, x, v)
        operate_tree(c2, x, v * x)

    helper(l, v)
    if r + 1 < len(c1):
        helper(r + 1, -v)


def query_tree_intervals(c1, c2, l, r):

    def helper(x):
        return pref_of_tree(c1, x) * (x + 1) - pref_of_tree(c2, x)

    return helper(r) - helper(l - 1)


# === test start ===
c1, c2 = init_tree_intervals(arr_p)

operate_tree_intervals(c1, c2, 2, 4, 1)
assert [query_tree_intervals(c1, c2, x, x) for x in range(1, len(arr_p))] == [1, 3, 4, 5, 5]

operate_tree_intervals(c1, c2, 2, 4, -1)
assert [query_tree_intervals(c1, c2, x, x) for x in range(1, len(arr_p))] == [1, 2, 3, 4, 5]
# === test end ===

# === test start ===
mat = [list(range(1 + 5 * x, 6 + 5 * x)) for x in range(5)]
mat_p = [[0] + [0] * len(mat[0])] + [[0] + row for row in mat]
# === test end ===

# 单点操作，区间查询


# def init_tree2(mat_p):
#     c = [[0] * len(mat_p[0]) for _ in range(len(mat_p))]
#     for i in range(1, len(c)):
#         for j in range(1, len(c[0])):
#             operate_tree2(c, i, j, mat_p[i][j])
#     return c


# def init_tree2(mat_p):
#     c = [row[:] for row in mat_p]
#
#     for i in range(1, len(c)):
#         i_p = i + lb(i)  # p stands for parent.
#         if i_p < len(c):
#             for j in range(1, len(c[0])):
#                 c[i_p][j] += c[i][j]
#
#     for i in range(1, len(c)):
#         for j in range(1, len(c[0])):
#             j_p = j + lb(j)  # p stands for parent.
#             if j_p < len(c[0]):
#                 c[i][j_p] += c[i][j]
#
#     return c


def prefix2(mat_p):
    pref_row = [list(accumulate(row)) for row in mat_p]
    pref_col = [list(accumulate(col)) for col in zip(*pref_row)]
    return [list(row) for row in zip(*pref_col)]


def init_tree2(mat_p):
    pref2 = prefix2(mat_p)
    c = [[0] * len(mat_p[0]) for _ in range(len(mat_p))]
    for i in range(1, len(c)):
        for j in range(1, len(c[0])):
            c[i][j] = pref2[i][j] - pref2[i - lb(i)][j] - pref2[i][j - lb(j)] + pref2[i - lb(i)][j - lb(j)]
    return c


def operate_tree2(c, x, y, v):
    i = x
    while i < len(c):
        j = y
        while j < len(c[0]):
            c[i][j] += v
            j += lb(j)
        i += lb(i)


def pref_of_tree2(c, x, y):
    res = 0
    i = x
    while i > 0:
        j = y
        while j > 0:
            res += c[i][j]
            j -= lb(j)
        i -= lb(i)
    return res


def query_tree2(c, i1, j1, i2, j2):
    return (
        pref_of_tree2(c, i2, j2)
        - pref_of_tree2(c, i1 - 1, j2)
        - pref_of_tree2(c, i2, j1 - 1)
        + pref_of_tree2(c, i1 - 1, j1 - 1)
    )


# === test start ===
c = init_tree2(mat_p)

operate_tree2(c, 3, 3, 1)

tmp = [row[:] for row in mat_p]
tmp[3][3] += 1

assert all(all(query_tree2(c, x, y, x, y) == tmp[x][y] for y in range(1, len(c[0]))) for x in range(1, len(c)))

operate_tree2(c, 3, 3, -1)

tmp[3][3] -= 1

assert all(all(query_tree2(c, x, y, x, y) == tmp[x][y] for y in range(1, len(c[0]))) for x in range(1, len(c)))
# === test end ===


# 区间操作，单点查询
def differ2(mat_p):
    diff_row = [[0] + [b - a for a, b in pairwise(row)] for row in mat_p]
    diff_col = [[0] + [b - a for a, b in pairwise(col)] for col in zip(*diff_row)]
    return [list(row) for row in zip(*diff_col)]


def init_tree2_interval(mat_p):
    diff2 = differ2(mat_p)
    return init_tree2(diff2)


def operate_tree2_interval(c, i1, j1, i2, j2, v):
    for i, si in ((i1, 1), (i2 + 1, -1)):
        if not i < len(c):
            continue
        for j, sj in ((j1, 1), (j2 + 1, -1)):
            if not j < len(c[0]):
                continue
            operate_tree2(c, i, j, v * si * sj)


def query_tree2_interval(c, x, y):
    return pref_of_tree2(c, x, y)


# === test start ===
c = init_tree2_interval(mat_p)

operate_tree2_interval(c, 2, 2, 4, 4, 1)

tmp = [row[:] for row in mat_p]
for i in range(2, 5):
    for j in range(2, 5):
        tmp[i][j] += 1

assert all(all(query_tree2_interval(c, x, y) == tmp[x][y] for y in range(1, len(c[0]))) for x in range(1, len(c)))


operate_tree2_interval(c, 2, 2, 4, 4, -1)

for i in range(2, 5):
    for j in range(2, 5):
        tmp[i][j] -= 1

assert all(all(query_tree2_interval(c, x, y) == tmp[x][y] for y in range(1, len(c[0]))) for x in range(1, len(c)))
# === test end ===


# 区间操作，区间查询
def init_tree2_intervals(mat_p):
    diff2 = differ2(mat_p)
    c1 = init_tree2(diff2)
    c2 = init_tree2([[e * i for j, e in enumerate(row)] for i, row in enumerate(diff2)])
    c3 = init_tree2([[e * j for j, e in enumerate(row)] for i, row in enumerate(diff2)])
    c4 = init_tree2([[e * i * j for j, e in enumerate(row)] for i, row in enumerate(diff2)])
    return c1, c2, c3, c4


def operate_tree2_intervals(c1, c2, c3, c4, i1, j1, i2, j2, v):

    def helper(x, y, v):
        operate_tree2(c1, x, y, v)
        operate_tree2(c2, x, y, v * x)
        operate_tree2(c3, x, y, v * y)
        operate_tree2(c4, x, y, v * x * y)

    for i, si in ((i1, 1), (i2 + 1, -1)):
        if not i < len(c1):
            continue
        for j, sj in ((j1, 1), (j2 + 1, -1)):
            if not j < len(c1[0]):
                continue
            helper(i, j, v * si * sj)


def query_tree2_intervals(c1, c2, c3, c4, i1, j1, i2, j2):

    def helper(x, y):
        return (
            pref_of_tree2(c1, x, y) * (x * y + x + y + 1)
            - pref_of_tree2(c2, x, y) * (y + 1)
            - pref_of_tree2(c3, x, y) * (x + 1)
            + pref_of_tree2(c4, x, y)
        )

    return helper(i2, j2) - helper(i1 - 1, j2) - helper(i2, j1 - 1) + helper(i1 - 1, j1 - 1)


# === test start ===
c1, c2, c3, c4 = init_tree2_intervals(mat_p)

operate_tree2_intervals(c1, c2, c3, c4, 2, 2, 4, 4, 1)

tmp = [row[:] for row in mat_p]
for i in range(2, 5):
    for j in range(2, 5):
        tmp[i][j] += 1

assert all(
    all(query_tree2_intervals(c1, c2, c3, c4, i, j, i, j) == tmp[i][j] for j in range(1, 6)) for i in range(1, 6)
)

operate_tree2_intervals(c1, c2, c3, c4, 2, 2, 4, 4, -1)

for i in range(2, 5):
    for j in range(2, 5):
        tmp[i][j] -= 1

assert all(
    all(query_tree2_intervals(c1, c2, c3, c4, i, j, i, j) == tmp[i][j] for j in range(1, 6)) for i in range(1, 6)
)
# === test end ===

# 全局第k小

# === test start ===
arr = list(range(-30, 30, 10))  # -> [-30, -20, -10, 0, 10, 20]

k = 3
# === test end ===

# print(f"{sorted(arr)[k - 1]=!r}")


# 二分 -> O((logn)**2)
def kth_bisect(arr, k):
    min_val = min(arr)
    max_val = max(arr)

    length = max_val - min_val + 1
    cnt = [0] * length

    for n in arr:
        cnt[n - min_val] += 1

    cnt_p = [0] + cnt  # index -> n - min_val; cnt_p[index + 1] -> cnt[index] -> n

    c = init_tree(cnt_p)

    # 求最小的x, 使得cnt_pref_p[x] >= k.
    # x: 1-based index
    # x - 1 -> 0-based index
    # x - 1 + min_val -> n: the kth num
    # return min(x for x in range(1, length + 1) if pref_of_tree(c, x) >= k) - 1 + min_val

    l, r = 1, length
    while l < r:
        mid = (l + r) // 2
        if pref_of_tree(c, mid) >= k:
            r = mid
        else:
            l = mid + 1

    return l - 1 + min_val


# === test start ===
assert kth_bisect(arr, k) == -10
# === test end ===

# import bisect
#
#
# def kth_bisect(arr, k):  # -> O(nlogn)
#     min_val = min(arr)
#     max_val = max(arr)
#
#     length = max_val - min_val + 1
#     cnt = [0] * length
#
#     for n in arr:
#         cnt[n - min_val] += 1
#
#     cnt_p = [0] + cnt  # index -> n - min_val; cnt_p[index + 1] -> cnt[index] -> n
#
#     c = init_tree(cnt_p)
#
#     cnt_pref_p = [pref_of_tree(c, x) for x in range(length + 1)]  # 开销严重，不能每次都算。
#     cnt_pref = cnt_pref_p[1:]
#
#     return bisect.bisect_left(cnt_pref, k) + min_val
#
#
# print(kth_bisect(arr, k))


# 倍增 -> O(logn)
def kth_bilift(arr, k):
    min_val = min(arr)
    max_val = max(arr)

    length = max_val - min_val + 1
    cnt = [0] * length

    for n in arr:
        cnt[n - min_val] += 1

    cnt_p = [0] + cnt  # index -> n - min_val; cnt_p[index + 1] -> cnt[index] -> n

    c = init_tree(cnt_p)

    pos, sum_val = 0, 0
    step = 1 << (length.bit_length() - 1)

    while step:
        next = pos + step
        if next < len(c) and sum_val + c[next] < k:
            sum_val += c[next]
            pos = next
        step >>= 1

    return pos + min_val  # pos + 1 - 1 + min_val


# === test start ===
assert kth_bilift(arr, k) == -10
# === test end ===

# 全局逆序对

# === test start ===
arr = [2, 4, 5, 3, 1]
# === test end ===


# def find_inversion(arr):  # -> O(n**2)
#     count = 0
#     for i in range(len(arr) - 1):
#         for j in range(i + 1, len(arr)):
#             if arr[i] > arr[j]:
#                 count += 1
#     return count
#
#
# print(f"{find_inversion(arr)=!r}")


def find_inversions(arr):  # -> O(nlogn)
    min_val = min(arr)
    max_val = max(arr)

    length = max_val - min_val + 1
    cnt = [0] * length
    cnt_p = [0] + cnt

    c = init_tree(cnt_p)

    count = 0
    for e in reversed(arr):  # 逆序迭代arr
        index = e - min_val + 1  # e -> 1-based index

        # pref_of_tree(c, index - 1) -> 树中比e小的元素数量
        # 逆序迭代 -> 这些元素的下标一定大于e的下标，即j > i
        count += pref_of_tree(c, index - 1)

        # 将e加入树中
        # c维护的是权值数组，因此只需自增1
        operate_tree(c, index, 1)

    return count


# === test start ===
assert find_inversions(arr) == 6
# === test end ===

# 维护不可差分的信息
# e.g. c[x] == max(a[x - lb(x) + 1], ..., a[x])
# e.g. c[x] == min(a[x - lb(x) + 1], ..., a[x])
# e.g. c[x] == gcd(a[x - lb(x) + 1], ..., a[x])

# === test start ===
arr = [2, 4, 5, 3, 1]
arr_p = [0] + arr
# === test end ===


# 即O(n)建树的方法一，但是要把c[j] += c[i]修改为c[j] = max(c[j], c[i]).
def init_tree_max(arr_p):  # -> O(n)
    c = arr_p[:]
    for i in range(1, len(c)):
        j = i + lb(i)  # j = (i | i - 1) + 1
        if j < len(c):
            c[j] = max(c[j], c[i])
    return c


# 修改不可差分的树状数组时，需要重建c[x]及其所有祖先；
# for c[i] in (c[x] and its ancestors):
# 它们各自的子节点的信息没有受到影响；
# 因此是正确的，可以直接使用。
# 枚举c[u]的子节点：
# 设：u = s * 2**(k + 1) + 2**k
# 则：c[u]有k个儿子：c[u - 2**0], c[u - 2**1], ..., c[u - 2**(k - 1)]
def operate_tree_max(c, x, v, arr_p):  # -> O((logn)**2)
    arr_p[x] += v
    i = x
    while i < len(c):
        # c[i] = arr_p[i]
        # j = 1
        # while j < lb(i):
        #     c[i] = max(c[i], c[i - j])
        #     j <<= 1

        # c[i] = max(arr_p[i], max(c[i - (1 << t)] for t in range(lb(i).bit_length() - 1)))  # i == 1 -> range(0) -> max(empty_generator) -> error!
        # c[i] = max([arr_p[i]] + [c[i - (1 << t)] for t in range(lb(i).bit_length() - 1)])  # 生成列表并拼接，稍慢
        c[i] = max(arr_p[i], *(c[i - (1 << t)] for t in range(lb(i).bit_length() - 1)))
        i += lb(i)


def query_tree_max(c, l, r, arr_p):  # -> O((logn)**2)
    tmp = float("-inf")
    while l <= r:
        previous = r - lb(r)  # r & r - 1
        if previous + 1 >= l:  # previous + 1 -> 区间右端点
            tmp = max(tmp, c[r])
            r = previous
        else:
            tmp = max(tmp, arr_p[r])
            r -= 1
    return tmp


# === test start ===
c = init_tree_max(arr_p)

operate_tree_max(c, 4, 3, arr_p)
assert query_tree_max(c, 2, 4, arr_p) == 6

operate_tree_max(c, 4, -3, arr_p)
assert query_tree_max(c, 2, 4, arr_p) == 5
# === test end ===
