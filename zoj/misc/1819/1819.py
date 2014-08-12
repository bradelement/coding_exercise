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
    if i == 1 or i == n:
        return 1
    if i == 0 or i > n:
        return 0

    return i * stirling(n-1, i) + stirling(n-1, i-1)

d = int(sys.stdin.readline().strip())
for _ in xrange(d):
    n, m = map(int, sys.stdin.readline().strip().split())
    print s(n, m)
