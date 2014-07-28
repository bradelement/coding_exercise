#include "cstdio"
#include "algorithm"
#include "vector"
using namespace std;

struct Edge
{
    int x, y, len;
    bool operator< (const Edge &e) const {
        return len < e.len;
    }
};

const int MAXN = 505;
Edge hub[MAXN*MAXN/2];
int n, m, pre[MAXN];

int find(int x)
{
    if (x == pre[x]) return x;
    return pre[x] = find(pre[x]);
}

void input()
{
    scanf("%d%d", &n, &m);
    for (int i=0; i<n; i++) {
        pre[i] = i;
    }
    for (int i=0; i<m; i++) {
        scanf("%d%d%d", &hub[i].x, &hub[i].y, &hub[i].len);
        if (hub[i].len == 0) {
            int a = find(hub[i].x);
            int b = find(hub[i].y);
            if (a != b) {
                pre[b] = a;
            }
        }
    }
}

void kruskal()
{
    sort(hub, hub+m);

    int sum = 0;
    for (int i=0; i<m; i++) {
        int a = find(hub[i].x);
        int b = find(hub[i].y);
        if (a!=b) {
            pre[b] = a;
            sum += hub[i].len;
        }
    }

    printf("%d\n", sum);
}

int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);

    while (t--) {
        input();
        kruskal();
    }    
    return 0;
}