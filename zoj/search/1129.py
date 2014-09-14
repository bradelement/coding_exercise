import sys
import Queue
from collections import defaultdict

def bfs(graph, d):
    que = Queue.Queue()
    name = 'Erdos, P.'
    d[name] = 0
    que.put(name)

    while not que.empty():
        name = que.get()
        for n in graph[name]:
            if n not in d:
                d[n] = d[name] + 1
                que.put(n)


casen = 1
while 1:
    p, n = map(int, sys.stdin.readline().strip().split())
    if p == 0 and n == 0: break

    graph = defaultdict(set)

    for i in xrange(p):
        line = sys.stdin.readline().strip()
        authors, paper = line.split(': ')
        authors = authors.split(', ')
        authors = [', '.join(authors[i:i+2]) for i in xrange(0, len(authors), 2)]
        
        for i in xrange(len(authors)):
            for j in xrange(i+1, len(authors)):
                graph[authors[i]].add(authors[j])
                graph[authors[j]].add(authors[i])


    d = {}
    bfs(graph, d)

    print 'Database #%d' % casen
    casen += 1
    for i in xrange(n):
        name = sys.stdin.readline().strip()
        num = str(d[name]) if name in d else 'infinity'
        print '%s: %s' % (name, num)

    print ''


