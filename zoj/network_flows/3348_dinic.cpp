#include "cstdio"
#include "cstring"
#include "vector"
#include "queue"
#include "map"
#include "string"

const int MAXN = 64;
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
int n, m;
char a[16], b[16], res[16];
int src, sink;
int relation[MAXN][MAXN];

std::map<std::string, int> name_to_id;

int id(std::string s)
{
    if (name_to_id.count(s)) return name_to_id[s];

    int _id = name_to_id.size();
    name_to_id[s] = _id;
    return _id;
}

bool gao()
{
    dinic.init();
    name_to_id.clear();
    memset(relation, 0, sizeof(relation));

    std::map<int, int> rank;
    for (int i=0; i<m; i++) {
        scanf("%s%s%s", a, b, res);
        int ida = id(a), idb = id(b);

        if (res[0] == 'w') {//win
            ++rank[ida];
        }
        else {
            ++rank[idb];
        }
    }

    std::string dd("DD");
    scanf("%d", &m);
    for (int i=0; i<m; i++) {
        scanf("%s%s", a, b);
        if (a == dd || b == dd) {
            ++rank[id(dd)];
        }
        else {
            ++relation[id(a)][id(b)];
        }
    }

    src = n; sink = src + 1;
    int full = 0, row;
    for (int i=0; i<n; i++) {
        if (i == id(dd)) continue;
        row = 0;
        for (int j=0; j<n; j++) {
            if (relation[i][j]) {
                row += relation[i][j];
                dinic.add_edge(i, j, relation[i][j]);
            }
        }
        dinic.add_edge(src, i, row);
        full += row;

        int lim = rank[id(dd)] - 1 - rank[i];
        if (lim < 0) return false;
        dinic.add_edge(i, sink, lim);
    }

    return dinic.maxflow(src, sink) == full;
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d", &n, &m)) {
        puts(gao() ? "Yes" : "No");
    }
    return 0;
}