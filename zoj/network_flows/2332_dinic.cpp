#include "cstdio"
#include "cstring"
#include "vector"
#include "queue"

const int MAXN = 128;
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
        for (int i=0; i<MAXN; i++) G[i].clear();
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
int N, M, D, tmp;
int r1, c1, r2, c2;
int gem[16][16];
int src, sink;

bool gao()
{
    dinic.init();

    scanf("%d%d", &N, &M);
    src = MAXN-2; sink = MAXN-1;
    int full = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            scanf("%d", &gem[i][j]);
            full += gem[i][j];
            dinic.add_edge(src, i*N+j, gem[i][j]);
        }
    }
    scanf("%d", &D);
    for (int i=0; i<D; i++) {
        scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
        dinic.add_edge(r1*N+c1, r2*N+c2, inf);
        dinic.add_edge(r2*N+c2, r1*N+c1, inf);
    }

    int base = N*M;
    for (int i=0; i<N; i++) {
        scanf("%d", &tmp);
        for (int j=0; j<M; j++) {
            dinic.add_edge(i*N+j, base+i, inf);
        }
        dinic.add_edge(base+i, sink, tmp);
    }
    base = N*M+N;
    for (int i=0; i<M; i++) {
        scanf("%d", &tmp);
        for (int j=0; j<N; j++) {
            dinic.add_edge(j*N+i, base+i, inf);
        }
        dinic.add_edge(base+i, sink, tmp);
    }

    return dinic.maxflow(src, sink) == full;
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--) {
        puts(gao() ? "Yes" : "No");
    }

    return 0;
}