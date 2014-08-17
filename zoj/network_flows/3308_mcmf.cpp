#include "cstdio"
#include "cstring"
#include "vector"
#include "queue"
#include "algorithm"

using namespace std;

const int MAXR = 16;
const int MAXN = MAXR * MAXR;
const int inf = 0x12345678;

struct Edge
{
    int from, to, cap, flow, cost;
    Edge(int a=0, int b=0, int c=0, int d=0, int e=0): from(a), to(b), cap(c), flow(d), cost(e) {}
};

struct MCMF {//minimum cost max flow
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[MAXN];
    int inq[MAXN]; //是否在队列中
    int d[MAXN];   //distance
    int p[MAXN];   //上一条弧
    int a[MAXN];   //可改进量

    void init(int n) {
        this->n = n;
        for (int i=0; i<n; i++) {
            G[i].clear();
        }
        edges.clear();
    }

    void add_edge(int from, int to, int cap, int cost) {
        edges.push_back(Edge(from, to, cap, 0, cost));
        edges.push_back(Edge(to, from, 0, 0, -cost));
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool spfa(int s, int t, int &flow, int &cost) {
        for (int i=0; i<n; i++) {
            d[i] = inf;
        }
        memset(inq, 0, sizeof(inq));
        d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = inf;

        queue<int> Q;
        Q.push(s);
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            inq[u] = 0;

            for (int i=0; i<G[u].size(); i++) {
                Edge &e = edges[G[u][i]];
                if (e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if (!inq[e.to]) {
                        Q.push(e.to);
                        inq[e.to] = 1;
                    }
                }
            }
        }

        if (d[t] == inf) return false; //s-t不联通
        flow += a[t];
        cost += d[t] * a[t];
        int u = t;
        while (u != s) {
            edges[p[u]].flow += a[t];
            edges[p[u]^1].flow -= a[t];
            u = edges[p[u]].from;
        }

        return true;
    }

    int min_cost(int s, int t) {
        int flow = 0, cost = 0;
        while (spfa(s, t, flow, cost));

        return cost;
    }

    void mcmf_helper(int s, int t, int &flow, int &cost) {
        flow = cost = 0;
        while (spfa(s, t, flow, cost));
    }
};

MCMF solver;
int R, C, N, K;
int grid[MAXR][MAXR];
int src, sink, supers;
int sx[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
int sy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

int id(int i, int j)
{
    return (i-1)*C+j;
}

bool valid(int i, int j)
{
    return i>=1 && i<=R && j>=1 && j<=C;
}

int cost(int i, int j, int ii, int jj, int type)
{
    if (type == 1) {
        return grid[i][j] * grid[ii][jj];
    }
    else if (type == 2) {
        return grid[i][j] + grid[ii][jj];
    }
    else {
        return max(grid[i][j], grid[ii][jj]);
    }
}

void input()
{
    solver.init(R*C+3);
    src = 0; sink = R*C+1; supers = sink+1;
    for (int i=1; i<=R; i++) {
        for (int j=1; j<=C; j++) {
            scanf("%d", &grid[i][j]);
            if ((i+j) % 2 == 0) {//black
                solver.add_edge(src, id(i, j), 1, 0);
            }
            else {
                solver.add_edge(id(i, j), sink, 1, 0);
            }
        }
    }

    int type, r, c;
    for (int i=0; i<N; i++) {
        scanf("%d%d%d", &type, &r, &c);
        for (int j=0; j<8; j++) {
            int xx = r + sx[j];
            int yy = c + sy[j];
            if (valid(xx, yy)) {
                solver.add_edge(id(r, c), id(xx, yy), 1, cost(r, c, xx, yy, type));
            }
        }
    }

    solver.add_edge(supers, src, K, 0);
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d%d%d", &R, &C, &N, &K)) {
        input();
        int f, c;
        solver.mcmf_helper(supers, sink, f, c);
        if (f == K) {
            printf("%d\n", c);
        }
        else {
            printf("-1\n");
        }
    }
    return 0;
}