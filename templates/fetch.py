from pyquery import PyQuery as pq
import urllib2, sys, time

def to_str(s):
    if type(s) == unicode:
        s = s.encode('utf8')

    return s.strip()

def fetch(url):
    print >> sys.stderr, 'fetch ', url
    req = urllib2.Request(url)
    req.add_header('User-Agent', 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/37.0.2062.103 Safari/537.36')
    stream = urllib2.urlopen(req)
    content = stream.read()
    #print >> sys.stderr, 'content ', content
    return content

#------------------------------------------------------------
def main():
    url = 'http://acm.zju.edu.cn/onlinejudge/showUserStatus.do?userId=47890'
    content = fetch(url)
    d = pq(content)
    ret = d('blockquote > div > a')
    for r in ret:
        print to_str(r.text)


if __name__ == '__main__':
    main()
