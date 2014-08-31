import sys

print 'Problem 4 by team x'
for line in sys.stdin:
    line = line.strip()
    n = int(line)

    m = 1
    p = 0
    while m % n:
        if m < n:
            p += 1
        m *= 10
        
    print "\n1 / %s =" % line
    print "0." + "0" * (p-1) + str(m / n)

print 'End of problem 4 by team x'

