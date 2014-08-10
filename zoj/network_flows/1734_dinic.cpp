#include "cstdio"
#include "cstring"
#include "vector"
#include "queue"

struct Edge
{
    int to, cap, rev;
    Edge(int a=0, int b=0, int c=0): to(a), cap(b), rev(c) {}
};

const int MAXN = 128;
const int inf = 0x12345678;
std::vector<Edge> edges[MAXN];
int level[MAXN], iter[MAXN];

int n, np, nc, m;
int src, sink;

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
    for (int i=0; i<=n+1; i++) {
        edges[i].clear();
    }

    int u, v, z;
    for (int i=0; i<m; i++) {
        scanf(" (%d,%d)%d", &u, &v, &z);
        add_edge(u, v, z);
    }
    src = n; sink = n+1;
    for (int i=0; i<np; i++) {
        scanf(" (%d)%d", &u, &z);
        add_edge(src, u, z);
    }
    for (int i=0; i<nc; i++) {
        scanf(" (%d)%d", &u, &z);
        add_edge(u, sink, z);
    }

}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d%d%d", &n, &np, &nc, &m)) {
        input();
        printf("%d\n", dinic(src, sink));
    }
    return 0;
}