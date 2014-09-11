import sys

def pri(n, w):
    print '%-29s%5d' % (n, w)

print 'Program 2 by team X'
book_shelf = []
maxwidth = int(sys.stdin.readline())
curwidth = 0
bw = {}

for line in sys.stdin:

    command = line[0:9].rstrip()
    if command == 'ADD':
        book = line[9:39].rstrip()
        width = int(line[39:])
        if book not in bw:
            bw[book] = width

        curwidth += width
        book_shelf.insert(0, book)
        while curwidth > maxwidth:
            n = book_shelf.pop()
            curwidth -= bw[n]

    elif command == 'CHECKOUT':
        book = line[9:39].rstrip()
        curwidth -= bw[book]
        book_shelf.remove(book)

    elif command == 'RETURN':
        book = line[9:39].rstrip()
        book_shelf.insert(0, book)
        curwidth += bw[book]
        while curwidth > maxwidth:
            n = book_shelf.pop()
            curwidth -= bw[n]

    elif command == 'PRINT':
        for n in book_shelf:
            pri(n, bw[n])
        pri('AVAILABLE SHELF SPACE:', maxwidth - curwidth)
        print ''


print 'End of program 2 by team X'