import sys

def num_to_str(num):
    ret = []
    while num != 0:
        ret.append(chr(ord('a') + (num-1)%26))
        num /= 26

    return ''.join(reversed(ret))

def str_to_num(s):
    ret = 0
    for c in s:
        ret = ret * 26 + ord(c) - ord('a') + 1

    return ret

def f(n):
    ret = []
    while n >= 1000:
        ret.append('%03d' % (n % 1000))
        n /= 1000
    ret.append(str(n))
    return ','.join(reversed(ret))



for line in sys.stdin:
    line = line.strip()
    if line == '*': break

    try:
        line = int(line)
        print '%-22s%s' % (num_to_str(line), f(line))
        continue
    except:
        print '%-22s%s' % (line, f(str_to_num(line)))
