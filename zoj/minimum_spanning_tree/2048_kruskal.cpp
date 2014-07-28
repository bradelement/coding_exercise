#include "cstdio"
#include "cmath"
#include "algorithm"
using namespace std;

struct Edge
{
    int x, y, len;
    bool operator< (const Edge &e) const {
        return len < e.len;
    }
};

const int MAXN = 751;
int N, M, edge_count;
int group;

pair<int, int> loc[MAXN];
Edge edges[MAXN * MAXN];
int pre[MAXN];

double square(int x)
{
    return x * x;
}

int find(int x)
{
    if (x == pre[x]) return x;
    return pre[x] = find(pre[x]);
}

void input()
{
    scanf("%d", &N);
    for (int i=1; i<=N; i++) {
        scanf("%d%d", &loc[i].first, &loc[i].second);
        pre[i] = i;
    }
    edge_count = 0;
    group = N;
    for (int i=1; i<=N; i++) {
        for (int j=i+1; j<=N; j++) {
            edges[edge_count].x = i;
            edges[edge_count].y = j;
            edges[edge_count].len = square(loc[i].first-loc[j].first) + \
                square(loc[i].second-loc[j].second);
            edge_count++;
        }
    }
    sort(edges, edges+edge_count);

    scanf("%d", &M);
    int a, b;
    for (int i=1; i<=M; i++) {
        scanf("%d%d", &a, &b);
        a = find(a); b = find(b);
        if (a != b) {
            pre[a] = b;
            group--;
        }
    }
}

void kruskal()
{
    int a, b;
    if (group == 1) return;
    for (int i=0; i<edge_count; i++) {
        a = find(edges[i].x);
        b = find(edges[i].y);
        if (a!=b) {
            printf("%d %d\n", edges[i].x, edges[i].y);
            pre[a] = b;
            if (--group == 1) break;
        }
    }
}

int main(int argc, char const *argv[])
{
    int casen;
    scanf("%d", &casen);
    for (int i=0; i<casen; i++) {
        input();
        kruskal();
        if (i != casen-1) {
            printf("\n");
        }
    }

    return 0;
}