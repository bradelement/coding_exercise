import sys

def cache(f):
    d = {}
    def wrapper(n, i):
        key = str(n) + '++' + str(i)
        if key not in d:
            d[key] = f(n, i)
        return d[key]
    return wrapper

@cache
def stirling(n, i):
    if i == 0 or i > n:
        return 0
    if i == 1 or i == n:
        return 1

    return i * stirling(n-1, i) + stirling(n-1, i-1)

def gao(n):
    return sum([stirling(n, i) for i in xrange(1, n+1)])

for line in sys.stdin:
    n = int(line.strip())
    if n == 0: break;
    print n, gao(n)
