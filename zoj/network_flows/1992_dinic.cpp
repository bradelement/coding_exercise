#include "cstdio"
#include "cstring"
#include "vector"
#include "queue"

const int MAXN = 256;
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
        for (int i=0; i<MAXN; i++) {
            G[i].clear();
        }
        m = 0;
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

/*
欧拉回路：
无向图: 每个顶点的度数都是偶数。
有向图: 每个顶点的入度等于出度。
混合图: 网络流~。
    1. 把无向边随便定向，计算每个点的入度和出度。
    如有顶点的出入度差为奇数，则无欧拉回路。

    2. 构造网络流，无向边随意定向并add_edge, cap为1。
    新建src, sink. 对于入大于出的点u连接(u, sink) cap为diff/2
    对于出大于入的点v连接(src, v) cap为diff/2
    查看是否有满流即可。。。
*/

Dinic dinic;
int m, s;
int in[MAXN], out[MAXN];
int src, sink;
int b[MAXN][MAXN];

bool gao()
{
    dinic.init();
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(b, 0, sizeof(b));

    scanf("%d%d", &m, &s);
    int x, y, d;

    for (int i=0; i<s; i++) {
        scanf("%d%d%d", &x, &y, &d);
        if (d == 0) {
            b[x][y]++;
        }
        out[x]++;
        in[y]++;
    }

    for (int i=1; i<=m; i++) {
        if ((in[i]-out[i]) & 1) {
            return false;
        }
    }
    for (int i=1; i<=m; i++) {
        for (int j=1; j<=m; j++) {
            if (b[i][j]) {
                dinic.add_edge(i, j, b[i][j]);
            }
        }
    }

    src = 0; sink = m+1;
    int full = 0;
    for (int i=1; i<=m; i++) {
        if (in[i] > out[i]) {
            dinic.add_edge(i, sink, (in[i] - out[i]) / 2);
        }
        else if (in[i] < out[i]) {
            dinic.add_edge(src, i, (out[i] - in[i]) / 2);
            full += (out[i] - in[i]) / 2;
        }
    }

    return dinic.maxflow(src, sink) == full;
}

int main(int argc, char const *argv[])
{
    int casen;
    scanf("%d", &casen);

    while (casen--) {
        bool ret = gao();
        if (ret) {
            puts("possible");
        }
        else {
            puts("impossible");
        }
    }

    return 0;
}

