#include "cstdio"
#include "queue"
#include "cstring"
#include "algorithm"

struct Edge
{
    int u, v, c, next;
};

const int MAXN = 32;
const int MAXE = 2048;
const int inf = 0x12345678;
int edn; //num of edges
int father[MAXN];
int dist[MAXN];
Edge edges[MAXE];
int src, sink;
int n, m;
std::queue<int> que;

void addedge(int u, int v, int c)
{
    edges[edn].u = u; edges[edn].v = v; edges[edn].c = c;
    edges[edn].next = father[u]; father[u] = edn++;

    edges[edn].u = v; edges[edn].v = u; edges[edn].c = 0;
    edges[edn].next = father[v]; father[v] = edn++;
}

bool bfs()
{
    while (!que.empty()) que.pop();
    memset(dist, -1, sizeof(dist));
    dist[src] = 0;
    que.push(src);

    while (!que.empty()) {
        int cur = que.front(); que.pop();
        for (int i=father[cur]; i!=-1; i=edges[i].next) {
            int u = edges[i].v;
            if (dist[u] == -1 && edges[i].c > 0) {
                dist[u] = dist[cur] + 1;
                que.push(u);
            }
        } 
    }
    return dist[sink] != -1;
}

int dfs(int p, int delta)
{
    if (p == sink) return delta;
    int ret = 0;
    for (int i=father[p]; i!=-1 && ret<delta; i=edges[i].next) {
        int u = edges[i].v;
        if (edges[i].c > 0 && dist[u]==dist[p]+1) {
            int dd = dfs(u, std::min(edges[i].c, delta-ret));
            ret += dd;
            edges[i].c -= dd;
            edges[i^1].c += dd;
        }
    }
    if (!ret) dist[p] = -2;
    return ret;
}

int dinic()
{
    int ret = 0, tmp;
    while (bfs()) {
        while (tmp = dfs(src, inf)) {
            ret += tmp;
        }
    }
    return ret;
}

void input()
{
    edn = 0;
    memset(father, -1, sizeof(father));
    scanf("%d%d", &m, &n);
    src = m; sink = n;
    char s[4];
    int c;
    for (int i=0; i<m; i++) {
        scanf("%s%d", s, &c);
        if (s[0] == 'I') {
            addedge(src, i, inf);
        }
        for (int j=0, tmp; j<c; j++) {
            scanf("%d", &tmp);
            addedge(i, tmp, inf);
            addedge(tmp, i, 1);
        }
    }
}

int main(int argc, char const *argv[])
{
    int casen;
    scanf("%d", &casen);
    while (casen--) {
        input();
        int ans = dinic();
        if (ans >= inf) {
            printf("PANIC ROOM BREACH\n");
        }
        else {
            printf("%d\n", ans);
        }
    }

    return 0;
}