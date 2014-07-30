#include "cstdio"
#include "cstring"

const int MAXN = 101;
int N, M;
int weight[MAXN];
double rate[MAXN][MAXN];
double dis[MAXN];
int visited[MAXN];

void input()
{
    for (int i=1; i<N; i++) {
        scanf("%d", &weight[i]);
    }
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=N; j++) {
            rate[i][j] = 0;
        }
    }
    int a, b;
    double c;
    for (int i=0; i<M; i++) {
        scanf("%d%d%lf", &a, &b, &c);
        if (rate[a][b] < 1-c) {
            rate[a][b] = rate[b][a] = 1-c;
        }
    }
}

double dijkstra()
{
    memset(visited, 0, sizeof(visited));
    memset(dis, 0, sizeof(dis));

    int now = N;
    dis[now] = 1;
    visited[now] = 1;
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=N; j++) {
            if (!visited[j] && dis[j] < dis[now] * rate[now][j]) {
                dis[j] = dis[now] * rate[now][j];
            }
        }

        double t = 0;
        for (int j=1; j<=N; j++) {
            if (!visited[j] && dis[j] > t) {
                t = dis[j];
                now = j;
            }
        }
        visited[now] = 1;
    }
    double ret = 0;
    for (int j=1; j<N; j++) {
        ret += dis[j] * weight[j];
    }
    return ret;
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d", &N, &M)) {
        input();
        printf("%.2lf\n", dijkstra());
    }
    return 0;
}