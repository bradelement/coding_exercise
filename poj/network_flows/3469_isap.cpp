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
    
    void init(int n, int m) {
        this->n = n;
        this->m = m;
        edges.clear();
        for (int i=0; i<MAXN; i++) {
            G[i].clear();
        }
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

Isap isap;
int n, m;
int src, sink;

void input()
{
    int a, b, w;
    src = 0; sink = n+1;

    isap.init(n+2, 2*n+m);
    for (int i=1; i<=n; i++) {
        scanf("%d%d", &a, &b);
        isap.add_edge(src, i, a);
        isap.add_edge(i, sink, b);
    }
    for (int i=0; i<m; i++) {
        scanf("%d%d%d", &a, &b, &w);
        isap.add_edge(a, b, w);
        isap.add_edge(b, a, w);
    }
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d", &n, &m)) {
        input();
        printf("%d\n", isap.maxflow(src, sink));
    }
    return 0;
}

