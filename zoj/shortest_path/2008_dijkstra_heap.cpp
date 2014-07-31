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
bool visited[MAXN];
std::priority_queue<Edge> que;

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
    std::fill(visited, visited+P+1, false);
    std::fill(dis, dis+P+1, inf);

    while (!que.empty()) que.pop();
    int now = 1, cur, curwei, maxt;
    dis[now] = 0; visited[now] = true;
    for (int i=0; i<ve[idx][now].size(); i++) {
        que.push(ve[idx][now][i]);
        dis[ve[idx][now][i].id] = ve[idx][now][i].weight;
    }

    int ret = 0;
    Edge ce;
    while (!que.empty()) {
        ce = que.top(); que.pop();
        if (!visited[ce.id]) {
            visited[ce.id] = true;
            ret += dis[ce.id];
            for (int i=0; i<ve[idx][ce.id].size(); i++) {
                cur = ve[idx][ce.id][i].id;
                curwei = ve[idx][ce.id][i].weight;
                if (!visited[cur] && dis[cur] > dis[ce.id]+curwei) {
                    dis[cur] = dis[ce.id] + curwei;
                    que.push(ve[idx][ce.id][i]);
                }
            }
        }
    }

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