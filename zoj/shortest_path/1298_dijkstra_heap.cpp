#include "cstdio"
#include "cstring"
#include "cstdlib"
#include "functional"
#include "algorithm"
#include "vector"
#include "queue"

struct Edge
{
    int end, len;
    Edge(int a=0, int b=0): end(a), len(b) {}
    bool operator< (const Edge &e) const {
        return len > e.len;
    }
};

const int MAXN = 512;
const int inf = 0x12345678;
const double eps = 1e-6;
int n, m;
std::vector<Edge> edges[MAXN];
int dis[MAXN];
typedef std::pair<int, int> Pii;
std::priority_queue<Pii> que;

void input()
{
    for (int i=1; i<=n; i++) {
        edges[i].clear();
    }

    int a, b, l;
    for (int i=0; i<m; i++) {
        scanf("%d%d%d", &a, &b, &l);
        edges[a].push_back(Edge(b, l));
        edges[b].push_back(Edge(a, l));
    }
}

void dijkstra(int start)
{
    std::fill(dis, dis+n+1, inf);
    while (!que.empty()) que.pop();
    dis[start] = 0;
    que.push(std::make_pair(start, 0));

    Pii ce;
    while (!que.empty()) {
        ce = que.top(); que.pop();
        int now = ce.first;
        if (dis[now] != ce.second) continue;
        
        for (int i=0; i<edges[now].size(); i++) {
            Edge &e = edges[now][i];
            if (dis[e.end] > dis[now] + e.len) {
                dis[e.end] = dis[now] + e.len;
                que.push(std::make_pair(e.end, dis[e.end]));
            }
        }
    }
}

void output(int casen)
{
    double maxedge = -1;
    int maxa, maxb;
    for (int i=1; i<=n; i++) {
        for (int j=0; j<edges[i].size(); j++) {
            int end = edges[i][j].end;
            int len = edges[i][j].len;
            if (abs(dis[i] - dis[end]) == len) continue;
            double tmp = (dis[i]+dis[end]+len) / 2.0;
            if (tmp > maxedge) {
                maxedge = tmp;
                maxa = i; maxb = end;
            } 
        }
    }
    double maxv = -1;
    int maxi;
    for (int i=1; i<=n; i++) {
        if (dis[i] > maxv) {
            maxv = dis[i];
            maxi = i;
        }
    }

    printf("System #%d\n", casen);
    if (maxedge > maxv+eps) {
        if (maxa > maxb) {
            std::swap(maxa, maxb);
        }
        printf("The last domino falls after %.1lf seconds, between key dominoes %d and %d.\n", maxedge, maxa, maxb);
    }
    else {
        printf("The last domino falls after %.1lf seconds, at key domino %d.\n", maxv, maxi);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    int casen = 1;
    while (scanf("%d%d", &n, &m), n) {
        input();
        dijkstra(1);
        output(casen++);
    }
    return 0;
}