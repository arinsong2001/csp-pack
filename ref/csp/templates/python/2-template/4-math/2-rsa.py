#!/usr/bin/env python3


def gcd(x, m):
    if m == 0:
        return x
    return gcd(m, x % m)


assert gcd(25, 7) == 1
assert gcd(25, 5) == 5


def gcd_ext(x, m):
    if m == 0:
        return x, 1, 0
    d, a, b = gcd_ext(m, x % m)
    return d, b, a - x // m * b


def inverse(x, m):
    return gcd_ext(x, m)[1] % m


assert inverse(25, 7) == 2


def expmod(x, y, m):
    if y == 0:
        return 1
    ans = expmod(x * x % m, y >> 1, m)
    if y & 1:
        ans = ans * x % m
    return ans


import random

x, y, m = (random.randint(1, 100) for _ in range(3))

assert expmod(x, y, m) == pow(x, y, m)


def gen_keys(p, q):
    n = p * q
    m = (p - 1) * (q - 1)
    e = random.randrange(n)
    gcd = gcd_ext(e, m)
    while gcd[0] != 1:
        e = random.randrange(n)
        gcd = gcd_ext(e, m)
    d = gcd[1] % m
    return e, d, n


def encrypt(msg: list[int], e, n):
    return [expmod(m, e, n) for m in msg]


def decrypt(cipher: list[int], d, n):
    return [expmod(c, d, n) for c in cipher]


e, d, n = gen_keys(5563, 8191)

raw_msg = [random.randint(1, 100) for _ in range(10)]

cipher = encrypt(raw_msg, e, n)

msg = decrypt(cipher, d, n)

assert raw_msg == msg
