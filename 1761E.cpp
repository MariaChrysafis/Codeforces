import random
import sys
import os
import math
import sys
class DisjointSetUnion :
    parent = []
    sz = []
    cc = 0

    def join (self, u: int, v: int) -> None:
        u = self.head(u)
        v = self.head(v)
        if u != v :
            self.cc -= 1
            if self.sz[u] > self.sz[v] :
                u, v = v, u
            self.sz[u] = self.sz[v] = self.sz[u] + self.sz[v]
            self.parent[u] = v

    def head (self, x: int) -> int:
        while x != self.parent[x] :
            x = self.parent[x]
        return x

    def __init__ (self, x: int) :
        self.sz = [1] * x
        self.parent = list(range(0, x))
        self.cc = x


def ans (arr: list[str]) -> list[int]:
    x = len(arr)
    dsu = DisjointSetUnion(x)
    deg = [0] * x
    heads = [0] * x
    for i in range(x) :
        for j in range(i, x) :
            if arr[i][j] == '1' :
                deg[i] += 1
                deg[j] += 1
                dsu.join(i, j)
    if dsu.cc == 1 :
        return []
    for i in range(x) :
        heads[i] = dsu.head(i)
    for i in range(x):
        if deg[i] == 0 :
            return [i]
    mn = x
    for i in range(x) :
        if deg[i] != dsu.sz[heads[i]] - 1 :
            mn = min(mn, deg[i])
    for i in range(x) :
        if deg[i] == mn and deg[i] != dsu.sz[heads[i]] - 1 :
            return [i]
    mn = x
    for i in range(x) :
        if i == heads[i] :
            mn = min(mn, dsu.sz[i])
    hd = 0
    for i in range(x) :
        if i == heads[i] and dsu.sz[i] == mn :
            hd = i
    pr = []
    for i in range(x) :
        if heads[i] == hd :
            pr.append(i)
    if dsu.cc == 2 :
        return pr
    index = pr[0]
    s = set(pr)
    for i in range(x) :
        if not (i in s) :
            return [index, i]
    return []

t = int(sys.stdin.readline())
for it in range(t) :
    n = int(sys.stdin.readline())
    inp = []
    for i in range(n) :
        inp.append(sys.stdin.readline())
    v = ans(inp)
    for i in range(len(v)) :
        v[i] += 1
    sys.stdout.write(str(len(v)) + '\n')
    print(*v)
