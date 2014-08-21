#include "cstdio"
#include "cstring"
#include "vector"
#include "queue"
#include "algorithm"

using namespace std;

const int MAXN = 1024;
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
};