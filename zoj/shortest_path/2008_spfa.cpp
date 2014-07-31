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
};

std::vector<Edge> ve[2][MAXN];
int dis[MAXN];
bool inQueue[MAXN];

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

int spfa(int idx)
{
    std::fill(inQueue, inQueue+P+1, false);
    std::fill(dis, dis+P+1, inf);
    std::queue<int> que;
    que.push(1);
    dis[1] = 0; inQueue[1] = true;
    
    int cur;
    while (!que.empty()) {
        cur = que.front(); que.pop();
        inQueue[cur] = false;
        for (int i=0; i<ve[idx][cur].size(); i++) {
            int id = ve[idx][cur][i].id;
            int weight = ve[idx][cur][i].weight;
            if (dis[cur]+weight < dis[id]) {
                dis[id] = dis[cur] + weight;
                if (!inQueue[id]) {
                    que.push(id);
                    inQueue[id] = true;
                }
            }
        }
    }
    int ret = 0;
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
        printf("%d\n", spfa(0)+spfa(1));
    }

    return 0;
}