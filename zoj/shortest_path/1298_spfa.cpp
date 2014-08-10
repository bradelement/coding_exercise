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
};

const int MAXN = 512;
const int inf = 0x12345678;
const double eps = 1e-6;
int n, m;
std::vector<Edge> edges[MAXN];
int dis[MAXN];
bool inQue[MAXN];

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

void spfa(int start)
{
    std::fill(dis, dis+n+1, inf);
    std::fill(inQue, inQue+n+1, false);
    
    std::queue<int> que;
    que.push(start);
    dis[start] = 0; inQue[start] = true;

    int cur, end, len;
    while (!que.empty()) {
        cur = que.front(); que.pop();
        inQue[cur] = false;

        for (int i=0; i<edges[cur].size(); i++) {
            end = edges[cur][i].end;
            len = edges[cur][i].len;
            if (dis[cur] + len < dis[end]) {
                dis[end] = dis[cur] + len;
                if (!inQue[end]) {
                    que.push(end);
                    inQue[end] = true;
                }
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
        spfa(1);
        output(casen++);
    }
    return 0;
}