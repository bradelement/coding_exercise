#include "cstdio"
#include "vector"
#include "algorithm"

const int MAXN = 1e6 + 1;
const int inf = 1e9+1;
int P, Q;
struct Edge {
    int id, weight;
    Edge(int a, int b): id(a), weight(b) {}
};

std::vector<Edge> ve[2][MAXN];
int dis[MAXN];
bool visited[MAXN];

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

long long dijkstra(int idx)
{
    std::fill(visited, visited+P+1, false);
    std::fill(dis, dis+P+1, inf);

    int now = 1, cur, curwei, maxt;
    dis[now] = 0; visited[now] = true;
    for (int i=1; i<P; i++) {
        for (int j=0; j<ve[idx][now].size(); j++) {
            cur = ve[idx][now][j].id;
            curwei = ve[idx][now][j].weight;
            if (!visited[cur] && dis[cur] > dis[now]+curwei) {
                dis[cur] = dis[now] + curwei;
            }
        }
        maxt = inf;
        for (int j=1; j<=P; j++) {
            if (!visited[j] && dis[j] < maxt) {
                maxt = dis[now = j];
            }
        }

        visited[now] = true;
    }
    long long ret = 0;
    for (int i=1; i<=P; i++) {
        ret += dis[i];
    }

    return ret;
}

int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    while (t--) {
        input();
        printf("%lld\n", dijkstra(0)+dijkstra(1));
    }

    return 0;
}