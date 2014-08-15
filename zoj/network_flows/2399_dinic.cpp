#include "cstdio"
#include "cstring"
#include "vector"
#include "queue"

const int MAXN = 1536;
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
int src, sink, x;
char line[32];
int sink_start, sink_end;

void input()
{
    dinic.init();
    src = n+m; sink = src+1;
    for (int i=0; i<n; i++) {
        dinic.add_edge(src, i, 1);
        scanf("%s", line);
        while (getchar() != '\n') {
            scanf("%d", &x);
            dinic.add_edge(i, x+n, 1);
        }
    }
    sink_start = dinic.m;
    for (int i=0; i<m; i++) {
        dinic.add_edge(n+i, sink, n);
    }
    sink_end = dinic.m;
}

bool check(int f)
{
    for (int i=sink_start; i<sink_end; i+=2) {
        dinic.edges[i].cap = f;
    }
    for (int i=0; i<dinic.m; i++) {
        dinic.edges[i].flow = 0;
    }
    return dinic.maxflow(src, sink) == n;
}

int main(int argc, char const *argv[])
{
    while (scanf("%d%d", &n, &m), n) {
        input();
        int ans = n;
        int l = n/m, r = n;
        while (l <= r) {
            int mid = (l+r) / 2;
            if (check(mid)) {
                r = mid - 1;
                ans = mid;
            }
            else {
                l = mid + 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}