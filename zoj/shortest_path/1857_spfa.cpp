#include "cstdio"
#include "cstring"
#include "vector"
#include "iostream"
#include "queue"
#include "algorithm"
#include "climits"

struct Edge
{
    int end, len;
    Edge(int a=0, int b=0): end(a), len(b) {}
};

const int MAXF = 100;
const int MAXN = 501;
const int inf = 0x3f3f3f3f;
int n, m;
int fire_stations[MAXF];
char line[32];
std::vector<Edge> edges[MAXN];
int dis[MAXN], dis2[MAXN];
bool inQue[MAXN];

void input()
{
    for (int i=0; i<n; i++) {
        scanf("%d", &fire_stations[i]);
    }
    for (int i=1; i<=m; i++) {
        edges[i].clear();
    }
    gets(line);
    int a, b, c;
    while (1) {
        if (!gets(line)) break;
        if (strcmp(line, "") == 0) break;
        sscanf(line, "%d%d%d", &a, &b, &c);
        edges[a].push_back(Edge(b, c));
        edges[b].push_back(Edge(a, c));
    }
}

void spfa(int start, int *dis)
{
    std::fill(inQue+1, inQue+m+1, false);
    std::queue<int> que;
    que.push(start);
    dis[start] = 0; inQue[start] = true;

    int cur, end, len;
    while (!que.empty()) {
        cur = que.front(); que.pop();
        inQue[cur] = false;

        for (int i=0; i<edges[cur].size(); i++) {
            end = edges[cur][i].end;
            len = edges[cur][i].len;
            if (dis[cur] + len < dis[end]) {
                dis[end] = dis[cur] + len;
                if (!inQue[end]) {
                    que.push(end);
                    inQue[end] = true;
                }
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d", &n, &m)) {
        input();
        std::fill(dis+1, dis+m+1, inf);
        for (int i=0; i<n; i++) {
            spfa(fire_stations[i], dis);
        }
        int ans = 1, maxval = INT_MAX;
        for (int i=1; i<=m; i++) {
            if (dis[i] == 0) continue;
            for (int j=1; j<=m; j++) {
                dis2[j] = dis[j];
            }
            spfa(i, dis2);
            int mx = *std::max_element(dis2+1, dis2+m+1);
            if (mx < maxval) {
                maxval = mx;
                ans = i;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}