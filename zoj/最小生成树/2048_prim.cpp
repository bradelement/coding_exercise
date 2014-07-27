#include "cstdio"
#include "cstring"
#include "cmath"
#include "climits"
#include "utility"
using namespace std;

const int MAXN = 751;
int N, M;

pair<int, int> loc[MAXN];
double map[MAXN][MAXN];
double dis[MAXN];
int ud[MAXN];
int pre[MAXN];

double square(double x)
{
    return x * x;
}
double distance(int i, int j)
{
    return sqrt(square(loc[i].first - loc[j].first) + \
        square(loc[i].second - loc[j].second));
}

void input()
{
    scanf("%d", &N);
    for (int i=1; i<=N; i++) {
        scanf("%d%d", &loc[i].first, &loc[i].second);
    }
    for (int i=1; i<=N; i++) {
        for (int j=i+1; j<=N; j++) {
            map[i][j] = map[j][i] = distance(i, j);
        }
    }

    scanf("%d", &M);
    int a, b;
    for (int i=1; i<=M; i++) {
        scanf("%d%d", &a, &b);
        map[a][b] = map[b][a] = 0.0;
    }
}

void prim()
{
    memset(ud, 0, sizeof(ud));
    for (int i=1; i<=N; i++) {
        dis[i] = INT_MAX;
    }
    int now = 1;
    dis[now] = 0; ud[now] = 1;

    for (int i=1; i<N; i++) {
        for (int j=1; j<=N; j++) {
            if (!ud[j] && dis[j]>map[now][j]) {
                dis[j] = map[now][j];
                pre[j] = now;
            }
        }
        double mindis = INT_MAX;
        for (int j=1; j<=N; j++) {
            if (!ud[j] && dis[j]<mindis) {
                mindis = dis[now = j];
            }
        }
        ud[now] = 1;
        if (fabs(mindis) > 1e-6) {
            printf("%d %d\n", pre[now], now);
        }
    }
}


int main(int argc, char const *argv[])
{
    int casen;
    scanf("%d", &casen);
    for (int i=0; i<casen; i++) {
        input();
        prim();
        if (i != casen-1) {
            printf("\n");
        }
    }
    //while (1);
    return 0;
}