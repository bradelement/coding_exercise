#include "cstdio"
#include "cstring"
#include "vector"
#include "queue"

const int MAXN = 20480;
const int inf = 0x12345678;

struct Edge
{
    int from, to, cap, flow;
    Edge(int a=0, int b=0, int c=0, int d=0): from(a), to(b), cap(c), flow(d) {}
};

struct Dinic
{
    int n, m, s, t;
    std::vector<Edge> edges;
    std::vector<int> G[MAXN];
    bool vis[MAXN];
    int d[MAXN];
    int cur[MAXN];
    
    void init() {
        edges.clear();
    }
    
    void add_edge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool bfs() {
        memset(vis, 0, sizeof(vis));
        std::queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = 1;

        while (!Q.empty()) {
            int x = Q.front(); Q.pop();
            for (int i=0; i<G[x].size(); i++) {
                Edge &e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }

        return vis[t];
    }

    int dfs(int x, int a) {
        if (x == t || a == 0) return a;
        int flow = 0, f;
        for (int &i=cur[x]; i<G[x].size(); i++) {
            Edge &e = edges[G[x][i]];
            if (d[x]+1 == d[e.to] && (f=dfs(e.to, std::min(a, e.cap-e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }

    int maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        while (bfs()) {
            memset(cur, 0, sizeof(cur));
            flow += dfs(s, inf);
        }
        return flow;
    }
};

Dinic dinic;
int n, m;
int src, sink;

void input()
{
    int a, b, w;
    src = 0; sink = n+1;

    dinic.init();
    for (int i=1; i<=n; i++) {
        scanf("%d%d", &a, &b);
        dinic.add_edge(src, i, a);
        dinic.add_edge(i, sink, b);
    }
    for (int i=0; i<m; i++) {
        scanf("%d%d%d", &a, &b, &w);
        dinic.add_edge(a, b, w);
        dinic.add_edge(b, a, w);
    }
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d", &n, &m)) {
        input();
        printf("%d\n", dinic.maxflow(src, sink));
    }
    return 0;
}

