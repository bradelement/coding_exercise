#include "cstdio"
#include "cstring"
#include "vector"
#include "queue"

struct Edge
{
    int from, to, cap, flow;
    Edge(int a=0, int b=0, int c=0, int d=0): from(a), to(b), cap(c), flow(d) {}
};

const int MAXN = 128;
const int inf = 0x12345678;

struct EdmondKarp {
    int n, m;
    std::vector<Edge> edges;
    std::vector<int> G[MAXN];
    int a[MAXN];
    int p[MAXN];

    void init(int n) {
        for (int i=0; i<n; i++) {
            G[i].clear();
        }
        edges.clear();
    }

    void add_edge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    int max_flow(int s, int t) {
        int flow = 0;
        for (;;) {
            memset(a, 0, sizeof(a));
            std::queue<int> Q;
            Q.push(s);
            a[s] = inf;

            while (!Q.empty()) {
                int x = Q.front(); Q.pop();
                for (int i=0; i<G[x].size(); i++) {
                    Edge &e = edges[G[x][i]];
                    if (!a[e.to] && e.cap > e.flow) {
                        p[e.to] = G[x][i];
                        a[e.to] = std::min(a[x], e.cap-e.flow);
                        Q.push(e.to);
                    }
                }
                if (a[t]) break;
            }
            
            if (!a[t]) break;
            for (int u=t; u!=s; u=edges[p[u]].from) {
                edges[p[u]].flow += a[t];
                edges[p[u]^1].flow -= a[t];
            }
            flow += a[t];
        }
        return flow;
    }

};

EdmondKarp ekarp;

int n, np, nc, m;
int src, sink;

void input()
{
    ekarp.init(n+2);
    int u, v, z;
    for (int i=0; i<m; i++) {
        scanf(" (%d,%d)%d", &u, &v, &z);
        ekarp.add_edge(u, v, z);
    }
    src = n; sink = n+1;
    for (int i=0; i<np; i++) {
        scanf(" (%d)%d", &u, &z);
        ekarp.add_edge(src, u, z);
    }
    for (int i=0; i<nc; i++) {
        scanf(" (%d)%d", &u, &z);
        ekarp.add_edge(u, sink, z);
    }
}



int main(int argc, char const *argv[])
{
    while (~scanf("%d%d%d%d", &n, &np, &nc, &m)) {
        input();
        printf("%d\n", ekarp.max_flow(src, sink));
    }
    return 0;
}