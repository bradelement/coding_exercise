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
    bool operator< (const Edge &other) const {
        return len > other.len;
    }
};

const int MAXF = 100;
const int MAXN = 501;
const int inf = 0x3f3f3f3f;
int n, m;
int fire_stations[MAXF];
char line[32];
std::vector<Edge> edges[MAXN];
int dis[MAXN], dis2[MAXN];
bool visited[MAXN];

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

void dijkstra(int start, int *dis)
{
    std::fill(visited, visited+m+1, false);
    std::priority_queue<Edge> que;
    dis[start] = 0;
    visited[start] = true;
    for (int i=0; i<edges[start].size(); i++) {
        que.push(edges[start][i]);
        if (edges[start][i].len < dis[edges[start][i].end]) {
            dis[edges[start][i].end] = edges[start][i].len;
        }
    }

    Edge ce;
    while (!que.empty()) {
        ce = que.top(); que.pop();
        int now = ce.end;
        if (!visited[now]) {
            visited[now] = true;
            for (int i=0; i<edges[now].size(); i++) {
                int end = edges[now][i].end;
                int len = edges[now][i].len;
                if (!visited[end] && dis[end] > dis[now]+len) {
                    dis[end] = dis[now]+len;
                    que.push(edges[now][i]);
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
            dijkstra(fire_stations[i], dis);
        }
        int ans = 1, maxval = INT_MAX;
        for (int i=1; i<=m; i++) {
            if (dis[i] == 0) continue;
            for (int j=1; j<=m; j++) {
                dis2[j] = dis[j];
            }
            dijkstra(i, dis2);
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