#!/usr/bin/env python3


class DsuNaive:
    def __init__(self, n):  # holds elements from 0 to n - 1
        self.pa = list(range(n))
        self.size = [1] * n

    def find(self, x):
        # if self.pa[x] != x:
        #     self.pa[x] = self.find(self.pa[x])
        # return self.pa[x]
        while self.pa[x] != x:
            self.pa[x] = self.pa[self.pa[x]]
            x = self.pa[x]
        return x

    def unite(self, x, y):
        # 双写变量名 -> 变量的亲属
        xx, yy = self.find(x), self.find(y)
        if xx == yy:
            return False
        if self.size[xx] > self.size[yy]:
            xx, yy = yy, xx
        self.pa[xx] = yy
        self.size[yy] += self.size[xx]
        return True


def dsu_naive_test():
    # n -> {e for e in range(n)}
    # m -> 操作次数，即进行unite和find的次数
    n, m = map(int, input().split())
    dsu = DsuNaive(n)
    for _ in range(m):
        operator, x, y = input().split()
        x, y = int(x), int(y)
        if operator == "u":  # unite
            dsu.unite(x, y)
        elif operator == "j":  # judge
            print("Y" if dsu.find(x) == dsu.find(y) else "N")
        else:
            raise Exception("illegal operation!")


# dsu_naive_test()


# 带删除并查集
class Dsu:
    def __init__(self, n, m):
        # [0, ..., n - 1] -> elements
        # [n, ..., 2 * n - 1] -> default virtual node
        # [2 * n, ..., 2 * n + m - 1] -> potential new virtual node
        self.pa = list(range(n, n * 2)) + list(range(n, n * 2 + m))

        # New virtual node starts here.
        self.id = n * 2

        # holds size for elements, default nodes and new nodes
        self.size = [1] * (n * 2 + m)

    def find(self, x):
        # if self.pa[x] != x:
        #     self.pa[x] = self.find(self.pa[x])
        # return self.pa[x]
        while self.pa[x] != x:
            self.pa[x] = self.pa[self.pa[x]]
            x = self.pa[x]
        return x

    def unite(self, x, y):
        xx, yy = self.find(x), self.find(y)
        if xx == yy:
            return False
        if self.size[xx] > self.size[yy]:
            xx, yy = yy, xx
        self.pa[xx] = yy
        self.size[yy] += self.size[xx]
        return True

    def erase(self, x):
        xx = self.find(x)
        self.pa[x] = self.id
        self.id += 1
        self.size[xx] -= 1

    def move(self, x, y):
        self.erase(x)
        self.unite(x, y)


def dsu_test():
    n, m = map(int, input().split())
    dsu = Dsu(n, m)
    for _ in range(m):
        operation = input().split()
        match operation[0]:
            case "u":  # unite
                x = int(operation[1])
                y = int(operation[2])
                dsu.unite(x, y)
            case "j":  # judge
                x = int(operation[1])
                y = int(operation[2])
                print("Y" if dsu.find(x) == dsu.find(y) else "N")
            case "e":  # erase
                x = int(operation[1])
                dsu.erase(x)
            case "m":  # move
                x = int(operation[1])
                y = int(operation[2])
                dsu.move(x, y)
            case _:
                raise Exception("illegal operation!")
    res = 0
    for i in range(n, dsu.id):
        if dsu.size[i] and i == dsu.find(i):
            res += 1
    print(f"{res} sets in total.")


# dsu_test()

# 带权并查集


# difference: 差分约束（只能处理差值约束）
class DsuDiff:
    def __init__(self, n):
        self.pa = list(range(n))
        self.weight = [0] * n
        self.size = [1] * n

    def find(self, x):
        if self.pa[x] != x:
            xx = self.find(self.pa[x])
            self.weight[x] += self.weight[self.pa[x]]
            self.pa[x] = xx
        return self.pa[x]

    def unite(self, x, y, w):  # value[x] - value[y] == w
        xx = self.find(x)
        yy = self.find(y)

        if xx == yy:
            return self.weight[x] - self.weight[y] == w

        if self.size[xx] > self.size[yy]:
            xx, yy = yy, xx
            x, y = y, x
            w = -w

        self.pa[xx] = yy
        self.weight[xx] = w + self.weight[y] - self.weight[x]
        self.size[yy] += self.size[xx]

        return True

    def check(self, x, y, w):
        xx = self.find(x)
        yy = self.find(y)

        if xx == yy:
            return self.weight[x] - self.weight[y] == w

        # 当(xx != yy)时，(value[x] - value[y] == w)是不能确定的。
        # 返回值如何，需要看题目要求。
        # return None
        # return False
        # raise Exception('unknown!')


# mod 2: 模二 -> 二分图、敌人关系、平等约束
class DsuMod2:
    def __init__(self, n):
        self.pa = list(range(n))
        self.weight = [0] * n
        self.size = [1] * n

    def find(self, x):
        if self.pa[x] != x:
            xx = self.find(self.pa[x])
            # self.weight[x] = (self.weight[x] + self.weight[self.pa[x]]) % 2
            self.weight[x] ^= self.weight[self.pa[x]]
            self.pa[x] = xx
        return self.pa[x]

    def unite(self, x, y, w):
        xx = self.find(x)
        yy = self.find(y)

        if xx == yy:
            # return (self.weight[x] - self.weight[y]) % 2 == w
            return self.weight[x] ^ self.weight[y] == w

        if self.size[xx] > self.size[yy]:
            xx, yy = yy, xx
            x, y = y, x
            # w = -w

        self.pa[xx] = yy
        # self.weight[xx] = (w + self.weight[y] - self.weight[x]) % 2
        self.weight[xx] = w ^ self.weight[x] ^ self.weight[y]
        self.size[yy] += self.size[xx]

        return True

    def check(self, x, y, w):
        xx = self.find(x)
        yy = self.find(y)

        if xx == yy:
            # return (self.weight[x] - self.weight[y]) % 2 == w % 2
            return self.weight[x] ^ self.weight[y] == w & 1

        # return None
        # return False
        # raise Exception('unknown!')


# mod 3: 模三 -> 食物链
class DsuMod3:
    def __init__(self, n):
        self.pa = list(range(n))
        self.weight = [0] * n
        self.size = [1] * n

    def find(self, x):
        if self.pa[x] != x:
            xx = self.find(self.pa[x])
            self.weight[x] = (self.weight[x] + self.weight[self.pa[x]]) % 3
            self.pa[x] = xx
        return self.pa[x]

    def unite(self, x, y, w):
        xx = self.find(x)
        yy = self.find(y)

        if xx == yy:
            return (self.weight[x] - self.weight[y]) % 3 == w

        if self.size[xx] > self.size[yy]:
            xx, yy = yy, xx
            x, y = y, x
            w = -w

        self.pa[xx] = yy
        self.weight[xx] = (w + self.weight[y] - self.weight[x]) % 3
        self.size[yy] += self.size[xx]

        return True

    def check(self, x, y, w):
        xx = self.find(x)
        yy = self.find(y)

        if xx == yy:
            return (self.weight[x] - self.weight[y]) % 3 == w % 3

        # return None
        # return False
        # raise Exception('unknown!')


# mod M: 模M
class DsuModM:
    def __init__(self, n, mod=None):
        self.pa = list(range(n))
        self.weight = [0] * n
        self.size = [1] * n
        self.mod = mod

    def _norm(self, res):
        if self.mod is None:
            return res
        return res % self.mod

    def find(self, x):
        if self.pa[x] != x:
            xx = self.find(self.pa[x])
            self.weight[x] = self._norm(self.weight[x] + self.weight[self.pa[x]])
            self.pa[x] = xx
        return self.pa[x]

    def unite(self, x, y, w):
        xx = self.find(x)
        yy = self.find(y)

        if xx == yy:
            return self._norm(self.weight[x] - self.weight[y]) == self._norm(w)

        if self.size[xx] > self.size[yy]:
            xx, yy = yy, xx
            x, y = y, x
            w = -w

        self.pa[xx] = yy
        self.weight[xx] = self._norm(w + self.weight[y] - self.weight[x])
        self.size[yy] += self.size[xx]

        return True

    def check(self, x, y, w):
        xx = self.find(x)
        yy = self.find(y)

        if xx == yy:
            return self._norm(self.weight[x] - self.weight[y]) == self._norm(w)

        # return None
        # return False
        # raise Exception('unknown!')


# distance: 距离约束
class DsuDist:
    def __init__(self, n):
        self.pa = list(range(n))
        self.weight = [0] * n
        self.size = [1] * n

    def find(self, x):
        if self.pa[x] != x:
            xx = self.find(self.pa[x])
            self.weight[x] += self.weight[self.pa[x]]
            self.pa[x] = xx
        return self.pa[x]

    def unite(self, x, y, w):
        xx = self.find(x)
        yy = self.find(y)

        if xx == yy:
            return self.weight[x] - self.weight[y] == w

        if self.size[xx] > self.size[yy]:
            xx, yy = yy, xx
            x, y = y, x
            w = -w

        self.pa[xx] = yy
        self.weight[xx] = w + self.weight[y] - self.weight[x]
        self.size[yy] += self.size[xx]

        return True

    def check(self, x, y, w):
        xx = self.find(x)
        yy = self.find(y)

        if xx == yy:
            return self.weight[x] - self.weight[y] == w

        # return None
        # return False
        # raise Exception('unknown!')

    def dist(self, x, y):
        xx = self.find(x)
        yy = self.find(y)

        if xx == yy:
            return abs(self.weight[x] - self.weight[y])

        # return None
        # return False
        # raise Exception('unknown!')


# 可回滚并查集
class DsuRollback:
    def __init__(self, n):
        self.pa = list(range(n))
        self.size = [1] * n
        self.hist = []

    def find(self, x):
        while self.pa[x] != x:
            x = self.pa[x]
        return x

    def unite(self, x, y):
        xx = self.find(x)
        yy = self.find(y)

        if xx == yy:
            self.hist.append(None)
            return False

        if self.size[xx] > self.size[yy]:
            xx, yy = yy, xx

        self.hist.append((xx, yy, self.size[yy]))

        self.pa[xx] = yy
        self.size[yy] += self.size[xx]

        return True

    def snapshot(self):
        return len(self.hist)

    def rollback(self):
        info = self.hist.pop()
        if info is None:
            return
        xx, yy, old_size = info  # 使用old_size -> 更通用
        self.pa[xx] = xx
        self.size[yy] = old_size

    def rollback_to(self, snap):
        while len(self.hist) > snap:
            self.rollback()
