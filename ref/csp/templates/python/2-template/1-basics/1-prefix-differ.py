#!/usr/bin/env python3

from itertools import accumulate, pairwise

arr = list(range(1, 6))
arr_p = [0] + arr


# itertools hack
def prefix(arr_p):
    return list(accumulate(arr_p))


# normal
def query(pref, l, r):
    return pref[r] - pref[l - 1]


# itertools hack
def differ(arr_p):
    return [arr_p[0]] + [b - a for a, b in pairwise(arr_p)]


# normal
def operate(diff, l, r, v):
    diff[l] += v
    if r + 1 < len(diff):
        diff[r + 1] -= v


pref = prefix(arr_p)
diff = differ(arr_p)

assert query(pref, 2, 4) == 9

operate(diff, 2, 4, 1)
arr_p_restored = prefix(diff)
assert all(arr_p_restored[i] - arr_p[i] == 1 for i in range(2, 5))
operate(diff, 2, 4, -1)
arr_p_restored = prefix(diff)
assert all(x == y for x, y in zip(arr_p, arr_p_restored))

mat = [list(range(1 + 5 * x, 6 + 5 * x)) for x in range(5)]
mat_p = [[0] + [0] * len(mat[0])] + [[0] + row for row in mat]


# itertools hack
def prefix2(mat_p):
    pref_row = [list(accumulate(row)) for row in mat_p]
    pref_col = [list(accumulate(col)) for col in zip(*pref_row)]
    return [list(row) for row in zip(*pref_col)]


# inclusion-exclusion expansion with sign enumeration: 使用符号枚举写法的容斥展开式
def query2(pref2, i1, j1, i2, j2):
    res = 0
    for di, si in ((i2, 1), (i1 - 1, -1)):
        for dj, sj in ((j2, 1), (j1 - 1, -1)):
            res += pref2[di][dj] * si * sj
    return res


# itertools hack
def differ2(mat_p):
    diff_row = [[row[0]] + [b - a for a, b in pairwise(row)] for row in mat_p]
    diff_col = [[col[0]] + [b - a for a, b in pairwise(col)] for col in zip(*diff_row)]
    return [list(row) for row in zip(*diff_col)]


# inclusion-exclusion expansion
def operate2(diff2, i1, j1, i2, j2, v):
    for di, si in ((i1, 1), (i2 + 1, -1)):
        if not di < len(diff2):
            continue
        for dj, sj in ((j1, 1), (j2 + 1, -1)):
            if not dj < len(diff2[0]):
                continue
            diff2[di][dj] += v * si * sj


pref2 = prefix2(mat_p)
diff2 = differ2(mat_p)

assert query2(pref2, 2, 2, 4, 4) == 117

operate2(diff2, 2, 2, 4, 4, 1)
mat_p_restored = prefix2(diff2)
assert all(all(mat_p_restored[i][j] - mat_p[i][j] == 1 for j in range(2, 5)) for i in range(2, 5))
operate2(diff2, 2, 2, 4, 4, -1)
mat_p_restored = prefix2(diff2)
assert all(all(x == y for x, y in zip(row, row_restored)) for row, row_restored in zip(mat_p, mat_p_restored))

cube = [[list(range(1 + 5 * x + 25 * y, 6 + 5 * x + 25 * y)) for x in range(5)] for y in range(5)]
n, m, l = len(cube), len(cube[0]), len(cube[0][0])
cube_p = [[[0] * (l + 1) for _ in range(m + 1)] for _ in range(n + 1)]
for i in range(1, n + 1):
    for j in range(1, m + 1):
        for k in range(1, l + 1):
            cube_p[i][j][k] = cube[i - 1][j - 1][k - 1]


# 固定其他维度，逐维计算
def prefix3(cube_p):
    pref3 = [[row[:] for row in plane] for plane in cube_p]

    for i in range(1, len(cube_p)):
        for j in range(1, len(cube_p[0])):
            for k in range(1, len(cube_p[0][0])):
                pref3[i][j][k] += pref3[i - 1][j][k]

    for i in range(1, len(cube_p)):
        for j in range(1, len(cube_p[0])):
            for k in range(1, len(cube_p[0][0])):
                pref3[i][j][k] += pref3[i][j - 1][k]

    for i in range(1, len(cube_p)):
        for j in range(1, len(cube_p[0])):
            for k in range(1, len(cube_p[0][0])):
                pref3[i][j][k] += pref3[i][j][k - 1]

    return pref3


# inclusion-exclusion expansion
def query3(pref3, i1, j1, k1, i2, j2, k2):
    res = 0
    for di, si in ((i2, 1), (i1 - 1, -1)):
        for dj, sj in ((j2, 1), (j1 - 1, -1)):
            for dk, sk in ((k2, 1), (k1 - 1, -1)):
                res += pref3[di][dj][dk] * si * sj * sk
    return res


# 固定其他维度，逐维计算
# 注意：需要反向for循环！
def differ3(cube_p):
    diff3 = [[row[:] for row in plane] for plane in cube_p]

    for i in range(len(cube_p) - 1, 0, -1):
        for j in range(len(cube_p[0]) - 1, 0, -1):
            for k in range(len(cube_p[0][0]) - 1, 0, -1):
                diff3[i][j][k] -= diff3[i - 1][j][k]

    for i in range(len(cube_p) - 1, 0, -1):
        for j in range(len(cube_p[0]) - 1, 0, -1):
            for k in range(len(cube_p[0][0]) - 1, 0, -1):
                diff3[i][j][k] -= diff3[i][j - 1][k]

    for i in range(len(cube_p) - 1, 0, -1):
        for j in range(len(cube_p[0]) - 1, 0, -1):
            for k in range(len(cube_p[0][0]) - 1, 0, -1):
                diff3[i][j][k] -= diff3[i][j][k - 1]

    return diff3


# inclusion-exclusion expansion
def operate3(diff3, i1, j1, k1, i2, j2, k2, v):
    for di, si in ((i1, 1), (i2 + 1, -1)):
        if not di < len(diff3):
            continue
        for dj, sj in ((j1, 1), (j2 + 1, -1)):
            if not dj < len(diff3[0]):
                continue
            for dk, sk in ((k1, 1), (k2 + 1, -1)):
                if not dk < len(diff3[0][0]):
                    continue
                diff3[di][dj][dk] += v * si * sj * sk


pref3 = prefix3(cube_p)
diff3 = differ3(cube_p)

assert query3(pref3, 2, 2, 2, 4, 4, 4) == 1701

operate3(diff3, 2, 2, 2, 4, 4, 4, 1)
cube_p_restored = prefix3(diff3)
assert all(
    all(all(cube_p_restored[i][j][k] - cube_p[i][j][k] == 1 for k in range(2, 5)) for j in range(2, 5))
    for i in range(2, 5)
)
operate3(diff3, 2, 2, 2, 4, 4, 4, -1)
cube_p_restored = prefix3(diff3)
assert all(
    all(all(x == y for x, y in zip(row, row_restored)) for row, row_restored in zip(plane, plane_restored))
    for plane, plane_restored in zip(cube_p, cube_p_restored)
)

# 总结：
#       # prefix    # query     # differ    # operate
# 1d    # hack      # normal    # hack      # normal
# 2d    # hack      # expansion # hack      # expansion
# 3d    # 逐维      # expansion # 逐维      # expansion
