import sys
#import pdb 
#pdb.set_trace() 
MAX_LEN = 256

while True:
    line = sys.stdin.readline()
    if line == '': break

    line = map(int, line.strip().split())
    N = line[0]
    num = sorted(line[1:])

    child = [0] * MAX_LEN
    child[1] = 100000 #dummy

    L = int(sys.stdin.readline())
    for i in xrange(1, L):
        line = map(int, sys.stdin.readline().strip().split())
        cur = 0

        for j in xrange(2**i, 2**(i+1)):
            if cur >= len(line): break
            if child[j/2] > 1:
                child[j] = line[cur]
                cur += 1
        
    a = [0] * MAX_LEN
    offset = [0] * MAX_LEN

    for level in xrange(L):
        for j in xrange(2**level, 2**(level+1)):
            if child[j] > 0:
                a[j] = offset[j] + child[j*2] 
                offset[2*j] = offset[j]
                offset[2*j+1] = a[j] + 1   

    ret = []
    def post_order(root):
        if child[root] > 0:
            post_order(root * 2)
            post_order(root * 2 + 1)
            ret.append(num[a[root]])

    post_order(1)
    print ' '.join(map(str, ret))


