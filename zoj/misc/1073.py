import sys

def circle(line, n):
    n = str(n)
    if len(n) < len(line):
        n = '0'*(len(line) - len(n)) + n

    return line in n+n

def gao(line):
    nn = int(line)
    for i in xrange(len(line)):
        n = nn * (i+1)
        if not circle(line, n):
            return False

    return True

def main():    
    for line in sys.stdin:
        line = line.strip()

        if gao(line):
            print "%s is cyclic" % line
        else:
            print "%s is not cyclic" % line

main()