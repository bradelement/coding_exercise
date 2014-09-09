import sys, math

def gao(n):
    s = n.split('.')[1]
    num = 0
    base = 1

    for c in s:
        base *= 8
        num = num * 8 + (ord(c) - ord('0'))

    shift_len = int(math.log(base, 2))
    num *= 5 ** shift_len
    num = str(num)
    if len(num) < shift_len:
        num = '0' * (shift_len-len(num)) + num

    while num[-1] == '0':
        num = num[:-1]
    
    return '0.' + num

for line in sys.stdin:
    line = line.strip()

    print "%s [8] = %s [10]" % (line, gao(line))