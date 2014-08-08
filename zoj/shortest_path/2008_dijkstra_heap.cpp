#include "cstdio"
#include "vector"
#include "algorithm"
#include "queue"

const int MAXN = 1e6 + 1;
const int inf = 1e9+1;
int P, Q;
struct Edge {
    int id, weight;
    Edge(int a=0, int b=0): id(a), weight(b) {}

    bool operator< (const Edge &e) const {
        return weight > e.weight;
    }
};

std::vector<Edge> ve[2][MAXN];
int dis[MAXN];
typedef std::pair<int, int> Pii;
std::priority_queue<Pii> que;

void input()
{
    for (int i=1; i<=P; i++) {
        ve[0][i].clear();
        ve[1][i].clear();
    }

    int a, b, c;
    scanf("%d%d", &P, &Q);
    for (int i=0; i<Q; i++) {
        scanf("%d%d%d", &a, &b, &c);
        ve[0][a].push_back(Edge(b, c));
        ve[1][b].push_back(Edge(a, c));
    }
}

int dijkstra(int idx)
{
    std::fill(dis, dis+P+1, inf);
    while (!que.empty()) que.pop();
    int start = 1;
    dis[start] = 0;
    que.push(std::make_pair(start, 0));

    Pii ce;
    while (!que.empty()) {
        ce = que.top(); que.pop();
        int now = ce.first;
        if (dis[now] != ce.second) continue;
        
        for (int i=0; i<ve[idx][now].size(); i++) {
            Edge &e = ve[idx][now][i];
            if (dis[e.id] > dis[now]+e.weight) {
                dis[e.id] = dis[now]+e.weight;
                que.push(std::make_pair(e.id, dis[e.id]));
            }
        }
    }
    
    int ret = 0;
    for (int i=1; i<=P; i++) ret += dis[i];
    return ret;
}

int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    while (t--) {
        input();
        printf("%d\n", dijkstra(0)+dijkstra(1));
    }

    return 0;
}