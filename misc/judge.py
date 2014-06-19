import sys, subprocess, random

def gao():
    r = random.randint(1, 21)
    c = random.randint(1, 21)
    try:
        le = random.randint(1, r*c/5)
    except:
        le = 0

    seq = [' '] + [chr(i) for i in xrange(ord('A'), ord('Z')+1)]
    s = ''
    for i in xrange(le):
        s += random.choice(seq)

    return '1\n' + '%d %d %s\n' % (r, c, s)

while True:
    p1 = subprocess.Popen('./my.out', stdin=subprocess.PIPE,\
        stdout=subprocess.PIPE)

    p2 = subprocess.Popen('./ans.out', stdin=subprocess.PIPE,\
        stdout=subprocess.PIPE, shell=True)

    ins = gao()
    print ins

    p1.stdin.write(ins)
    p2.stdin.write(ins)

    s1 = p1.stdout.read()
    s2 = p2.stdout.read()

    print s1, s2
    
    if s1 != s2:
        print 'myanswer', s1
        print 'true', s2
        break

