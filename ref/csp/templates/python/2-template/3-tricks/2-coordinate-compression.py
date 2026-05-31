#!/usr/bin/env python3

import bisect

# 原数组arr
arr = [100, 500, 200, 500]

# 去重有序数组xs -> [100, 200, 500]
xs = sorted(set(arr))  # xs stands for compressed coordinates set.

# 下标数组indices -> [0, 2, 1, 2]
# bisect_left(xs, e) -> index of e in xs
indices = [bisect.bisect_left(xs, e) for e in arr]
assert indices == [0, 2, 1, 2]

# index -> xs[index] -> arr
assert [xs[index] for index in indices] == arr

# 1-based version

arr = [-100, 100, 500, 200, 500]
arr_p = [0] + arr

# xs_p = sorted(set(arr_p))
xs = sorted(set(arr))  # 注意：不要直接对arr_p排序！
xs_p = [0] + xs

# indices_p = [bisect.bisect_left(xs_p, e) for e in arr_p]
indices = [bisect.bisect_left(xs, e) + 1 for e in arr]  # 注意：不能直接对xs_p二分！
indices_p = [0] + indices

assert [xs_p[index] for index in indices_p] == arr_p
