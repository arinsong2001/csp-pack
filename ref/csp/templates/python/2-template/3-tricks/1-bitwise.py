#!/usr/bin/env python3

# python符号优先级：
# tier0: ()
# tier1: ** > ~, (-)
# tier2: *, /, //, % > +, -
# tier3: <<, >>
# tier4: & > ^ > |
# tier5: <, >, ==

# Basics

# & -> 与

# 1. 判断奇偶


def is_odd(x):
    return bool(x & 1)


assert is_odd(13) is True and is_odd(14) is False


# 2. 判断第k位
def get_bit(x, k):
    return x >> k & 1


assert get_bit(13, 1) == 0 and get_bit(13, 2) == 1


# 3. 清除第k位
def remove_bit(x, k):
    return x & ~(1 << k)


assert remove_bit(13, 2) == 9


# | -> 或


# 1. 设置第k位
def set_bit(x, k):
    return x | 1 << k


assert set_bit(13, 1) == 15


# ^ -> 异或


# 1. 翻转第k位
def toggle_bit(x, k):
    return x ^ 1 << k


assert toggle_bit(13, 1) == 15 and toggle_bit(13, 2) == 9

# ~ -> 按位取反

# python的int是无限位补码的形式。
# 补码使得二进制加减不用再考虑符号。
# 取一个数的相反数就是“全部取反再加一”。
# 有：-x == ~x + 1
# 故：~x == -x - 1

# << -> 左移; >> -> 右移


# 1. 乘2的k次方
def multiply_by_2_to_the_k(x, k):
    return x << k


assert multiply_by_2_to_the_k(13, 1) == 26


# 1. 除以2的k次方
def divide_by_2_to_the_k(x, k):
    return x >> k


assert divide_by_2_to_the_k(13, 1) == 6


# Tricks

# lowbit


# 1. x & -x
# 效果：计算lowbit, 等价于(n ^ n & n - 1)
def lb(x):
    return x & -x


assert lb(13) == 1


# 获取lowbit的位置
def indexof_lb(x):
    return (x & -x).bit_length() - 1


assert indexof_lb(13) == 0


# 2. x & x - 1
# 效果：删除lowbit, 等价于计算(x - lb(x))
def remove_lb(x):
    return x & x - 1


assert remove_lb(13) == 12 and 13 - lb(13) == 12


# 判断是否为2的幂
def is_power_of_2(x):
    return x > 0 and x & x - 1 == 0


assert is_power_of_2(13) is False and is_power_of_2(16) is True


# 统计1的个数，等价于(x.bit_count())
def count_bits(x):
    cnt = 0
    while x:
        x &= x - 1
        cnt += 1
    return cnt


assert count_bits(13) == 3 and (13).bit_count() == 3


# 统计二进制位数，等价于(x.bit_length())
def lengthof_bits(x):
    length = 0
    while x:
        x >>= 1
        length += 1
    return length


assert lengthof_bits(13) == 4 and (13).bit_length() == 4


# 计算highbit
def hb(x):
    return 1 << x.bit_length() - 1 if x != 0 else 0


assert hb(13) == 8


# 3. x | x - 1
# 效果：lowbit右侧变1, 等价于计算(x + lb(x) - 1)
def fill_right_ones(x):
    return x | x - 1


assert fill_right_ones(13) == 13 and 13 + lb(13) - 1 == 13


# 4. (x | x - 1) + 1
# 效果：清除lowbit并进位，等价于计算(x + lb(x))
def add_lb(x):
    return (x | x - 1) + 1


assert add_lb(13) == 14 and 13 + lb(13) == 14


# 5. x ^ x - 1
# 效果：lowbit右侧变1, 左侧变0, 主要用于生成mask
def create_mask(x):
    return x ^ x - 1


assert create_mask(13) == 1


# 6. x & x + 1
# 效果：删除lowbit0右侧的1
def clear_trailing_ones(x):
    return x & x + 1


assert clear_trailing_ones(13) == 12


# 7. x | x + 1
# 效果：lowbit0 -> 1
def set_lowbit0(x):
    return x | x + 1


assert set_lowbit0(13) == 15


# 8. x ^ x + 1
# 效果：lowbit0 -> 1, 左侧变0
def extend_mask(x):
    return x ^ x + 1


assert extend_mask(13) == 3

# 集合

# 仅包含自然数的集合可以压缩转换成bitset.
# e.g. {0, 2, 3} -> 0b1101
# 通常用名为mask的变量存储bitset.

# 常用操作


# 1. 求集合大小
def mask_sizeof(mask):
    return mask.bit_count()


assert mask_sizeof(13) == 3


# 2. 判断元素是否在集合中
def mask_contains(mask, e):
    return bool(mask >> e & 1)


assert mask_contains(13, 0) is True and mask_contains(13, 1) is False


# 3. 添加元素
def mask_add(mask, e):
    return mask | 1 << e


assert mask_add(13, 1) == 15


# 4. 删除元素
def mask_remove(mask, e):
    return mask & ~(1 << e)


assert mask_remove(13, 0) == 12


# 5. 求交集
def mask_intersection(mask1, mask2):
    return mask1 & mask2


assert mask_intersection(13, 11) == 9


# 6. 求并集
def mask_union(mask1, mask2):
    return mask1 | mask2


assert mask_union(13, 11) == 15


# 7. 求集合异或
def mask_sym_diff(mask1, mask2):
    return mask1 ^ mask2


assert mask_sym_diff(13, 11) == 6


# 8. 求差集
def mask_difference(mask1, mask2):
    return mask1 & ~mask2


assert mask_difference(13, 11) == 4


# 9. 枚举子集
def enum_subsets(mask):
    subsets = []
    s = mask
    while True:
        subsets.append(s)
        if not s:
            break
        s = (s - 1) & mask
    return subsets


assert len(enum_subsets(13)) == 2**3
