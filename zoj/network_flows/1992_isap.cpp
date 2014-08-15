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

struct Isap
{
    int n, m, s, t;
    std::vector<Edge> edges;
    std::vector<int> G[MAXN];
    bool vis[MAXN];
    int d[MAXN];
    int cur[MAXN];
    int p[MAXN];
    int num[MAXN];
    
    void init(int n) {
        this->n = n;
        this->m = 0;
        edges.clear();
        for (int i=0; i<MAXN; i++) {
            G[i].clear();
        }
        memset(p, 0, sizeof(p));
        memset(d, 0, sizeof(d));
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
        Q.push(t);
        d[t] = 0;
        vis[t] = 1;

        while (!Q.empty()) {
            int x = Q.front(); Q.pop();
            for (int i=0; i<G[x].size(); i++) {
                Edge &e = edges[G[x][i]];
                if (!vis[e.to]) {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }

        return vis[s];
    }

    int augment() {
        int x = t, a = inf;
        while (x != s) {
            Edge &e = edges[p[x]];
            a = std::min(a, e.cap-e.flow);
            x = edges[p[x]].from;
        }
        x = t;
        while (x != s) {
            edges[p[x]].flow += a;
            edges[p[x]^1].flow -= a;
            x = edges[p[x]].from;
        }
        return a;
    }

    int maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        bfs();
        memset(num, 0, sizeof(num));
        for (int i=0; i<n; i++) {
            num[d[i]]++;
        }
        int x = s;
        memset(cur, 0, sizeof(cur));

        while (d[s] < n) {
            if (x == t) {
                flow += augment();
                x = s;
            }

            int ok = 0;
            for (int i=cur[x]; i<G[x].size(); i++) {
                Edge &e = edges[G[x][i]];
                if (e.cap > e.flow && d[x] == d[e.to] + 1) {//advance
                    ok = 1;
                    p[e.to] = G[x][i];
                    cur[x] = i;
                    x = e.to;
                    break;
                }
            }
            if (!ok) {//retreat
                int m = n - 1;
                for (int i=0; i<G[x].size(); i++) {
                    Edge &e = edges[G[x][i]];
                    if (e.cap > e.flow) {
                        m = std::min(m, d[e.to]);
                    }
                }
                if (--num[d[x]] == 0) break;
                num[d[x] = m+1]++;
                cur[x] = 0;
                if (x != s) x = edges[p[x]].from;
            }
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

Isap isap;
int m, s;
int in[MAXN], out[MAXN];
int src, sink;
int b[MAXN][MAXN];

bool gao()
{
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(b, 0, sizeof(b));

    scanf("%d%d", &m, &s);
    isap.init(m+2);
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
                isap.add_edge(i, j, b[i][j]);
            }
        }
    }

    src = 0; sink = m+1;
    int full = 0;
    for (int i=1; i<=m; i++) {
        if (in[i] > out[i]) {
            isap.add_edge(i, sink, (in[i] - out[i]) / 2);
        }
        else if (in[i] < out[i]) {
            isap.add_edge(src, i, (out[i] - in[i]) / 2);
            full += (out[i] - in[i]) / 2;
        }
    }

    return isap.maxflow(src, sink) == full;
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

