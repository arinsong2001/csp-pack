#!/usr/bin/env python3

import math


def era_sieve(n):
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False

    for i in range(2, math.isqrt(n) + 1):
        if is_prime[i]:
            for j in range(i * i, n + 1, i):
                is_prime[j] = False

    return [x for x in range(2, n + 1) if is_prime[x]]


def euler_sieve(n):
    is_composite = [False] * (n + 1)
    primes = []

    for i in range(2, n + 1):
        if not is_composite[i]:
            primes.append(i)

        for p in primes:
            if i * p > n:
                break

            is_composite[i * p] = True

            if i % p == 0:
                break

    return primes


# 筛法求最小质因数spf
def spf(n):
    is_composite = [False] * (n + 1)
    primes = []

    spf = [0] * (n + 1)
    spf[1] = 1

    for i in range(2, n + 1):
        if not is_composite[i]:
            primes.append(i)
            spf[i] = i

        for p in primes:
            if i * p > n:
                break

            is_composite[i * p] = True

            spf[i * p] = p
            if i % p == 0:
                break

    return spf


# 筛法求欧拉函数phi
def phi(n):
    is_composite = [False] * (n + 1)
    primes = []

    phi = [0] * (n + 1)
    phi[1] = 1

    for i in range(2, n + 1):
        if not is_composite[i]:
            primes.append(i)
            phi[i] = i - 1

        for p in primes:
            if i * p > n:
                break

            is_composite[i * p] = True

            if i % p == 0:
                phi[i * p] = phi[i] * p
                break

            phi[i * p] = phi[i] * (p - 1)

    return phi


# 筛法求莫比乌斯函数mu
def mu(n):
    is_composite = [False] * (n + 1)
    primes = []

    mu = [0] * (n + 1)
    mu[1] = 1

    for i in range(2, n + 1):
        if not is_composite[i]:
            primes.append(i)
            mu[i] = -1

        for p in primes:
            if i * p > n:
                break

            is_composite[i * p] = True

            if i % p == 0:
                mu[i * p] = 0
                break

            mu[i * p] = -mu[i]

    return mu


# 筛法求约数个数tau
def tau(n):
    is_composite = [False] * (n + 1)
    primes = []

    tau = [0] * (n + 1)
    tau[1] = 1

    # cnt: spf的幂次
    # 设：spf[x] -> p,
    # 有：x -> p^k * m, not p | m,
    # 则：cnt[x] -> k
    cnt = [0] * (n + 1)

    for i in range(2, n + 1):
        if not is_composite[i]:
            primes.append(i)
            tau[i] = 2
            cnt[i] = 1

        for p in primes:
            if i * p > n:
                break

            is_composite[i * p] = True

            if i % p == 0:
                cnt[i * p] = cnt[i] + 1
                tau[i * p] = tau[i] // (cnt[i] + 1) * (cnt[i] + 2)
                break

            cnt[i * p] = 1
            tau[i * p] = tau[i] * 2

    return tau


# 筛法求约数和sigma
def sigma(n):
    is_composite = [False] * (n + 1)
    primes = []

    sigma = [0] * (n + 1)
    sigma[1] = 1

    # sum_p: spf的等比和
    # 设：spf[x] -> p,
    # 有：x -> p^k * m, not p | m,
    # 则：sum_p = 1 + p + p^2 + p^3 + ... + p^k.
    sum_p = [0] * (n + 1)

    for i in range(2, n + 1):
        if not is_composite[i]:
            primes.append(i)
            sigma[i] = i + 1
            sum_p[i] = i + 1

        for p in primes:
            if i * p > n:
                break

            is_composite[i * p] = True

            if i % p == 0:
                sum_p[i * p] = sum_p[i] * p + 1
                sigma[i * p] = sigma[i] // sum_p[i] * sum_p[i * p]
                break

            sum_p[i * p] = p + 1
            sigma[i * p] = sigma[i] * (p + 1)

    return sigma


# 六合一：primes, spf, phi, mu, tau, sigma
def linear_sieve_all(n):
    primes = []
    is_composite = [False] * (n + 1)

    spf = [0] * (n + 1)

    phi = [0] * (n + 1)
    mu = [0] * (n + 1)
    tau = [0] * (n + 1)
    sigma = [0] * (n + 1)

    # 额外辅助数组
    cnt = [0] * (n + 1)  # 最小质因子幂次（给 tau 用）
    sum_p = [0] * (n + 1)  # 最小质因子幂和（给 sigma 用）

    # 初始化
    phi[1] = 1
    mu[1] = 1
    tau[1] = 1
    sigma[1] = 1
    spf[1] = 1

    for i in range(2, n + 1):
        # --- i 是质数 ---
        if not is_composite[i]:
            primes.append(i)

            spf[i] = i

            phi[i] = i - 1
            mu[i] = -1

            tau[i] = 2
            cnt[i] = 1

            sigma[i] = i + 1
            sum_p[i] = i + 1

        # --- 枚举质数 ---
        for p in primes:
            if i * p > n:
                break

            is_composite[i * p] = True
            spf[i * p] = p

            if i % p == 0:
                # ===== 同质因子 =====

                # phi
                phi[i * p] = phi[i] * p

                # mu（出现平方因子）
                mu[i * p] = 0

                # tau
                cnt[i * p] = cnt[i] + 1
                tau[i * p] = tau[i] // (cnt[i] + 1) * (cnt[i] + 2)

                # sigma
                sum_p[i * p] = sum_p[i] * p + 1
                sigma[i * p] = sigma[i] // sum_p[i] * sum_p[i * p]

                break

            else:
                # ===== 新质因子 =====

                # phi
                phi[i * p] = phi[i] * (p - 1)

                # mu
                mu[i * p] = -mu[i]

                # tau
                cnt[i * p] = 1
                tau[i * p] = tau[i] * 2

                # sigma
                sum_p[i * p] = p + 1
                sigma[i * p] = sigma[i] * (p + 1)

    return {
        "primes": primes,
        "spf": spf,
        "phi": phi,
        "mu": mu,
        "tau": tau,
        "sigma": sigma,
    }


res = linear_sieve_all(100)

assert euler_sieve(100) == res["primes"]
assert spf(100) == res["spf"]
assert phi(100) == res["phi"]
assert mu(100) == res["mu"]
assert tau(100) == res["tau"]
assert sigma(100) == res["sigma"]
