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
int matrix[MAXN][MAXN];
int dp[MAXN][MAXN];
int src, sink, n;

void input()
{
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            scanf("%d", &matrix[i][j]);
            if (i == j) matrix[i][j] = 0;
            dp[i][j] = matrix[i][j] == -1 ? inf : matrix[i][j];
        }
    }
    scanf("%d%d", &src, &sink);
}

void floyd()
{
    int tmp;
    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                tmp = dp[i][k] + dp[k][j];
                if (tmp < dp[i][j]) dp[i][j] = tmp;
            }
        }
    }
}

int gao()
{
    //if (dp[src][sink] == inf) return 0;

    dinic.init();
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (matrix[i][j] == -1) continue;
            if (dp[src][i]+matrix[i][j]+dp[j][sink] == dp[src][sink]) {
                dinic.add_edge(i, j, 1);
            }
        }
    }
    return dinic.maxflow(src, sink);
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d", &n)) {
        input();
        if (src == sink) {
            puts("inf");
            continue;
        }
        floyd();
        printf("%d\n", gao());
    }

    return 0;
}