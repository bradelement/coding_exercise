#include "cstdio"
#include "cmath"
#include "algorithm"

struct Edge
{
    int x, y;
    double len;
    bool operator< (const Edge &e) const {
        return len < e.len;
    }
};

const int N = 505;
Edge hub[N*N];
int n, m, S, pre[N];
std::pair<int, int> pos[N];

int find(int x)
{
    if (x == pre[x]) return x;
    return pre[x] = find(pre[x]);
}

void kruskal()
{
    double max_distance = -1;
    for (int i=1; i<=n; i++) {
        pre[i] = i;
    }
    std::sort(hub, hub+m);

    int count = 0;
    for (int i=0; i<m; i++) {
        int a = find(hub[i].x);
        int b = find(hub[i].y);
        if (a!=b) {
            pre[b] = a;
            if (hub[i].len > max_distance) max_distance = hub[i].len;
            if (count++ == n-1-S) break;
        }
    }

    printf("%.2lf\n", max_distance);
}

double distance(int i, int j)
{
    return sqrt(pow(pos[i].first-pos[j].first, 2) +
        pow(pos[i].second-pos[j].second, 2));
}

void input()
{
    scanf("%d%d", &S, &n);
    for (int i=1; i<=n; i++) {
        scanf("%d%d", &pos[i].first, &pos[i].second);
    }

    m = 0;
    for (int i=1; i<=n; i++) {
        for (int j=i+1; j<=n; j++) {
            hub[m].x = i;
            hub[m].y = j;
            hub[m].len = distance(i, j);
            ++m;
        }
    }
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