import sys, subprocess

while True:
    for i in xrange(1, 99999+1, 5):
        p1 = subprocess.Popen('./a.out', stdin=subprocess.PIPE,\
            stdout=subprocess.PIPE)

        p2 = subprocess.Popen('python duipai.py', stdin=subprocess.PIPE,\
            stdout=subprocess.PIPE, shell=True)

        p1.stdin.write(str(i)+'\n')
        p2.stdin.write(str(i)+'\n')

        s1 = p1.stdout.read()
        s2 = p2.stdout.read()

        if (i/5) % 10 == 0:
            print 'debug', i, s1.strip(), s2.strip()

        if s1 != s2:
            print 'num: ', i
            print 'myanswer', s1
            print 'true', s2
            break

    break

