#!/usr/bin/env python3

# general segment tree template

# operations supported：
# assign: sum, prod, min, max, gcd, lcm
# add: sum, min, max
# multiply: sum, product, min(a ≥ 0), max(a ≥ 0), gcd, lcm

M = 0x3B800001  # 可能会用到(especially prod & lcm), 需要自行修改代码。

import math


class SegTree:
    # === config ===

    def merge(self, x, y):
        match self.type:
            case "sum":
                return x + y
            case "prod":
                return x * y
            case "min":
                return min(x, y)
            case "max":
                return max(x, y)
            case "gcd":
                return math.gcd(x, y)
            case "lcm":
                return math.lcm(x, y)
            case _:
                raise Exception("wrong type!")

    def transform(self, x, a, b, range_length):
        match self.type:
            case "sum":
                return a * x + b * range_length

            case "prod":
                if a == 0:
                    return pow(b, range_length)
                if not b == 0:
                    raise Exception("product does not support add!")
                return x * pow(a, range_length)

            case "min" | "max":
                if not a >= 0:
                    raise Exception("min & max require a ≥ 0!")
                return a * x + b

            case "gcd":
                if a == 0:
                    return b
                if not b == 0:
                    raise Exception("gcd does not support add!")
                return a * x

            case "lcm":
                if a == 0:
                    return b
                if not b == 0:
                    raise Exception("lcm does not support add!")
                return a * x

            case _:
                raise Exception("wrong type!")

    def identity(self):
        match self.type:
            case "sum":
                return 0
            case "prod":
                return 1
            case "min":
                return float("inf")
            case "max":
                return float("-inf")
            case "gcd":
                return 0
            case "lcm":
                return 1
            case _:
                raise Exception("wrong type!")

    # === init ===

    def __init__(self, arr_p, type="sum"):
        if not len(arr_p) > 1:
            raise Exception("empty arr!")

        self.type = type

        self.length = len(arr_p) - 1

        self.tree = [0] * (4 * self.length)

        self.lazy_a = [1] * (4 * self.length)
        self.lazy_b = [0] * (4 * self.length)

        self.build(1, 1, self.length, arr_p)

    # === build ===

    def build(self, node, l, r, arr_p):
        if l == r:
            self.tree[node] = arr_p[l]
            return

        mid = (l + r) // 2

        self.build(node * 2, l, mid, arr_p)
        self.build(node * 2 + 1, mid + 1, r, arr_p)

        self.tree[node] = self.merge(self.tree[node * 2], self.tree[node * 2 + 1])

    # === apply ===

    def apply(self, node, l, r, a, b):
        self.tree[node] = self.transform(self.tree[node], a, b, r - l + 1)

        if l < r:
            self.lazy_a[node] = a * self.lazy_a[node]
            self.lazy_b[node] = a * self.lazy_b[node] + b

    # === push down ===

    def push_down(self, node, l, r):
        a = self.lazy_a[node]
        b = self.lazy_b[node]

        if a == 1 and b == 0:
            return

        mid = (l + r) // 2

        self.apply(node * 2, l, mid, a, b)
        self.apply(node * 2 + 1, mid + 1, r, a, b)

        self.lazy_a[node] = 1
        self.lazy_b[node] = 0

    # === push up ===

    def push_up(self, node):
        self.tree[node] = self.merge(self.tree[node * 2], self.tree[node * 2 + 1])

    # === update ===

    def update(self, ql, qr, a, b, node=1, l=1, r=None):
        if r is None:
            r = self.length

        if ql <= l and r <= qr:
            self.apply(node, l, r, a, b)
            return

        self.push_down(node, l, r)

        mid = (l + r) // 2

        if ql <= mid:
            self.update(ql, qr, a, b, node * 2, l, mid)
        if qr > mid:
            self.update(ql, qr, a, b, node * 2 + 1, mid + 1, r)

        self.push_up(node)

    # === operations ===

    def assign(self, ql, qr, v):
        return self.update(ql, qr, 0, v)

    def add(self, ql, qr, v):
        return self.update(ql, qr, 1, v)

    def multiply(self, ql, qr, v):
        return self.update(ql, qr, v, 0)

    # === query ===

    def query(self, ql, qr, node=1, l=1, r=None):
        if r is None:
            r = self.length

        if ql <= l and r <= qr:
            return self.tree[node]

        self.push_down(node, l, r)

        mid = (l + r) // 2

        res = self.identity()

        if ql <= mid:
            res = self.merge(res, self.query(ql, qr, node * 2, l, mid))

        if qr > mid:
            res = self.merge(res, self.query(ql, qr, node * 2 + 1, mid + 1, r))

        return res


# === sum test ===
arr = list(range(1, 6))
arr_p = [0] + arr

st = SegTree(arr_p)

st.assign(3, 5, 8)
assert [st.query(i, i) for i in range(1, 6)] == [1, 2, 8, 8, 8]

st.add(3, 5, 1)
assert [st.query(i, i) for i in range(1, 6)] == [1, 2, 9, 9, 9]

st.multiply(1, 3, 10)
assert [st.query(i, i) for i in range(1, 6)] == [10, 20, 90, 9, 9]

# range add, range gcd
# - solution 1:
# - diff of arr, provided that pref_of_tree(c, l) - pref_of_tree(c, l - 1) requires more time.
# - fenwick(point operate, range sum) for diff just to accelerate the query of arr_l.
# - seg_tree(range assign, range gcd) for abs(diff) of arr, abs(diff): [abs(x) for x in diff].
#
# - solution 2:
# - seg_tree(range add, range sum) for diff to operate diff and query arr_l.
# - seg_tree(range assign, range gcd) for diff of arr, since math.gcd() always returns a positive value.

arr = [60, 30, 20, 15, 12]
arr_p = [0] + arr

diff = [0] + [b - a for a, b in zip(arr_p, arr_p[1:])]

st_sum = SegTree(diff, "sum")
st_gcd = SegTree(diff, "gcd")


def range_add(l, r, v, st_sum=st_sum, st_gcd=st_gcd):
    st_sum.add(l, l, v)
    if r + 1 <= st_sum.length:
        st_sum.add(r + 1, r + 1, -v)

    st_gcd.assign(l, l, st_sum.query(l, l))
    if r + 1 <= st_sum.length:
        st_gcd.assign(r + 1, r + 1, st_sum.query(r + 1, r + 1))


def range_query(l, r, st_sum=st_sum, st_gcd=st_gcd):
    arr_l = st_sum.query(1, l)
    if l == r:
        return arr_l
    return math.gcd(arr_l, st_gcd.query(l + 1, r))


assert range_query(1, 2) == 30  # -> gcd(60, 30) -> 30

range_add(1, 2, 10)  # -> virtual arr: [70, 40, 20, 15, 12]
assert range_query(1, 2) == 10  # -> gcd(70, 40) -> 10
assert range_query(2, 3) == 20  # -> gcd(40, 20) -> 20

range_add(2, 3, 4)  # -> virtual arr: [70, 44, 24, 15, 12]
assert range_query(2, 3) == 4  # -> gcd(44, 24) -> 4
assert range_query(3, 5) == 3  # -> gcd(24, 15, 12) -> 3
