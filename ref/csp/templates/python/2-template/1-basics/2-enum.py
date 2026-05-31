#!/usr/bin/env python3

# counting pairs

import random

random.seed(0)
arr = random.sample(range(-100, 100), k=100)


# def count_pairs(arr: list[int]) -> int:
#     count = 0
#     for i in range(len(arr)):
#         for j in range(len(arr)):
#             if i == j:
#                 continue
#             if arr[i] + arr[j] == 0:
#                 count += 1
#     return count


# def count_pairs(arr: list[int]) -> int:
#     count = 0
#     for i in range(1, len(arr)):
#         for j in range(i):
#             if arr[i] + arr[j] == 0:
#                 count += 1
#     return count * 2


def count_pairs(arr: list[int]) -> int:
    count = 0
    min_val = min(arr)
    max_val = max(arr)
    M = max(abs(max_val), abs(min_val))  # -> 数组元素的界
    met = [False] * (2 * M + 1)
    for e in arr:
        if met[M - e]:
            count += 1
        met[M + e] = True
    return count * 2


assert count_pairs(arr) == 52

# lights out

# n == 5, m == 6
lights = [[0, 1, 1, 0, 1, 0], [1, 0, 0, 1, 1, 1], [0, 0, 1, 0, 0, 1], [1, 0, 0, 1, 0, 1], [0, 1, 1, 1, 0, 0]]

# 有上述灯泡矩阵，求操作矩阵（1代表按下，0代表不按），使得灯泡全灭。
# 操作规则：按下灯泡会导致灯泡及其上下左右邻居的状态改变：on/off -> off/on.

# 线索：
# 1. 第2次按下同一个按钮时，将抵消第1次按下时所产生的结果。因此，每个按钮最多只需要按下一次；
# 2. 各个按钮被按下的顺序对最终的结果没有影响；
# 3. 对第1行中每盏点亮的灯，按下第2行对应的按钮，就可以熄灭第1行的全部灯。如此重复下去，可以熄灭第1、2、3、4行的全部灯。

# 思路：
# 线索三表明：第1行操作完毕后，按下第2行对应的按钮，“可以”熄灭第1行的全部灯。
# 实际上这是唯一的方法。
# 因此，枚举第一行的所有操作，那之后，后续行的操作都是唯一的了。
# 操作完成后，除了最后一行，其余行必定都是熄灭状态。
# 最后，检查终行是否是熄灭状态即可。
# 注意用位操作加速、控资源。


def operate(lights=lights):
    # bi_lights = [int("".join(str(light) for light in line), 2) for line in lights]
    bi_lights = [int("".join(map(str, line)), 2) for line in lights]

    mask = (1 << 6) - 1

    res = []
    for i in range(1 << 6):
        bi_lights_copy = bi_lights[:]

        ops = [i]

        bi_lights_copy[0] ^= i ^ ((i << 1) & mask) ^ ((i >> 1) & mask)
        bi_lights_copy[1] ^= i

        for j in range(4):
            k = bi_lights_copy[j]
            ops.append(k)

            bi_lights_copy[j] ^= k
            bi_lights_copy[j + 1] ^= k ^ ((k << 1) & mask) ^ ((k >> 1) & mask)
            if j + 2 < 5:
                bi_lights_copy[j + 2] ^= k

        if bi_lights_copy[4] == 0:
            res.append(ops)

    return res


supposed = [["101001", "110101", "001011", "100100", "010000"]]
res = [[f"{num:06b}" for num in ops] for ops in operate()]

assert res == supposed
