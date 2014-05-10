# catalan 
# normal: f(2n) = C(2n, n) - C(2n, n-1) = C(2n, n) / n+1
# extend: f(n+m) = C(n+m, n) - C(n+m, n+1) (n >= m)
# more: see http://www.cnblogs.com/wuyuegb2312/p/3016878.html

import sys
from math import factorial


def ans2(n, m):
    if n < m: return 0
    # n 50, there are n+1 position
    # you choose m
    # first one's possibility is n/n+1
    # second is n-1/n
    # ...
    # m is n-m+1/n-m+2
    return factorial(n+m) * (n-m+1) / (n+1)

def C(n, r):
    return factorial(n) / factorial(r) / factorial(n-r)

def ans(n, m):
    if n < m: return 0
    if m == 0: return 1
    return C(n+m, n) - C(n+m, n+1)



casen = 1
for line in sys.stdin:
    n, m = map(int, line.strip().split())
    if n == 0 and m == 0: break

    print 'Test #%d:' % casen
    print ans(n, m) * factorial(n) * factorial(m)
    #print ans2(n, m)
    casen += 1
    sys.stdout.flush()
