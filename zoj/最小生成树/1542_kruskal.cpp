#include "cstdio"
#include "algorithm"
using namespace std;

struct Edge
{
    int x, y, len;
    bool operator< (const Edge &e) const {
        return len < e.len;
    }
};

const int N = 1001;
Edge hub[15001];
int n, m, pre[N], put[N];

void input()
{
    for (int i=0; i<m; i++) {
        scanf("%d%d%d", &hub[i].x, &hub[i].y, &hub[i].len);
    }
}

int find(int x)
{
    if (x == pre[x]) return x;
    return pre[x] = find(pre[x]);
}

void kruskal()
{
    int count = 0, maxlen = -1;
    for (int i=1; i<=n; i++) {
        pre[i] = i;
    }
    sort(hub, hub+m);

    for (int i=0; i<m; i++) {
        int a = find(hub[i].x);
        int b = find(hub[i].y);
        if (a!=b) {
            if (hub[i].len > maxlen) {
                maxlen = hub[i].len;
            }
            pre[b] = a;
            put[count++] = i;
            if (count == n-1) break;
        }
    }

    printf("%d\n%d\n", maxlen, count);
    for (int i=0; i<count; i++) {
        printf("%d %d\n", hub[put[i]].x, hub[put[i]].y);
    }
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d", &n, &m)) {
        input();
        kruskal();
    }    
    return 0;
}