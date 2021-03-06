#include "cstdio"
#include "queue"
#include "cstring"
#include "algorithm"
#include "vector"

struct Edge
{
    int to, cap, rev;
    Edge(int a=0, int b=0, int c=0): to(a), cap(b), rev(c) {}
};

const int MAXN = 24;
const int inf = 0x12345678;

std::vector<Edge> edges[MAXN];
int level[MAXN];
int iter[MAXN];
int m, n, src, sink;

void add_edge(int from, int to, int cap)
{
    edges[from].push_back(Edge(to, cap, edges[to].size()));
    edges[to].push_back(Edge(from, 0, edges[from].size()-1));
}

void bfs(int s)
{
    memset(level, -1, sizeof(level));
    std::queue<int> que;
    level[s] = 0;
    que.push(s);
    
    while (!que.empty()) {
        int v = que.front(); que.pop();
        for (int i=0; i<edges[v].size(); i++) {
            Edge &e = edges[v][i];
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    } 
}

int dfs(int v, int t, int f)
{
    if (v == t) return f;
    for (int &i=iter[v]; i<edges[v].size(); i++) {
        Edge &e = edges[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, std::min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                edges[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int dinic(int s, int t)
{
    int flow = 0, f;
    for (;;) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        while ((f = dfs(s, t, inf)) > 0) {
            flow += f;
        }
    }
}

void input()
{
    scanf("%d%d", &m, &n);
    src = m; sink = n;
    for (int i=0; i<=m; i++) {
        edges[i].clear();
    }
    char s[4];
    int c;
    for (int i=0; i<m; i++) {
        scanf("%s%d", s, &c);
        if (s[0] == 'I') {
            add_edge(src, i, inf);
        }
        for (int j=0, tmp; j<c; j++) {
            scanf("%d", &tmp);
            add_edge(i, tmp, inf);
            add_edge(tmp, i, 1);
        }
    }
}

int main(int argc, char const *argv[])
{
    int casen;
    scanf("%d", &casen);
    while (casen--) {
        input();
        int ans = dinic(src, sink);
        if (ans >= inf) {
            printf("PANIC ROOM BREACH\n");
        }
        else {
            printf("%d\n", ans);
        }
    }

    return 0;
}