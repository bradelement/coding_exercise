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

const int N = 32;
Edge hub[128];
int n, edge_num, pre[N];

void input()
{
    char s[3];
    int count, len, start, end;
    edge_num = 0;
    for (int i=0; i<n-1; i++) {
        scanf("%s%d", s, &count);
        start = s[0] - 'A' + 1;
        for (int j=0; j<count; j++) {
            scanf("%s%d", s, &len);
            end = s[0] - 'A' + 1;
            hub[edge_num].x = start;
            hub[edge_num].y = end;
            hub[edge_num].len = len;
            edge_num++;
        }
    }
}

int find(int x)
{
    if (x == pre[x]) return x;
    return pre[x] = find(pre[x]);
}

void kruskal()
{
    int sum = 0;
    for (int i=1; i<=n; i++) {
        pre[i] = i;
    }
    sort(hub, hub+edge_num);

    for (int i=0; i<edge_num; i++) {
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
    while (scanf("%d", &n), n) {
        input();
        kruskal();
    }    
    return 0;
}