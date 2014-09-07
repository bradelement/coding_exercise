# -*- coding:utf8 -*-
import sys, math

def cache(f):
    d = {}
    def wrapper(*args):
        if args not in d:
            d[args] = f(*args)

        return d[args]

    return wrapper


def c(n, m):
    return math.factorial(n) / math.factorial(m) / math.factorial(n-m)

@cache
#错排公式
def f(n):
    if n == 0: #for convenience
        return 1
    elif n == 1:
        return 0
    elif n == 2:
        return 1
    else:
        return (n-1) * (f(n-1) + f(n-2))

#错排公式的另一种计算方法
def f1(n):
    if n == 0:
        return 1
    return int(math.factorial(n) / math.e + 0.5)


def gao(n, m):
    #return c(n, m) * f1(n-m) * 1.0 / math.factorial(n)
    return c(n, m) * f(n-m) * 1.0 / math.factorial(n)


for line in sys.stdin:
    n, m = map(int, line.strip().split())
    print "%.8lf" % gao(n, m)
