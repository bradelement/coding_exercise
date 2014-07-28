#include "cstdio"
#include "cmath"
#include "climits"
#include "cstring"

const int MAXN = 101;
int N;

struct City
{
    double x, y;
};
City cities[MAXN];
double map[MAXN][MAXN];
double dis[MAXN];
int hash[MAXN];

double square(double x)
{
    return x*x;
}
double distance(int i, int j) {
    return sqrt(square(cities[i].x-cities[j].x) + \
        square(cities[i].y-cities[j].y));
}

double prim()
{
    double sum = 0;
    memset(hash, 0, sizeof(hash));
    for (int i=1; i<=N; i++) {
        dis[i] = INT_MAX;
    }
    int now = 1;
    dis[now] = 0; hash[now] = 1;

    for (int i=1; i<N; i++) {
        for (int j=1; j<=N; j++) {
            if (!hash[j] && dis[j]>map[now][j]) {
                dis[j] = map[now][j];
            }
        }
        for (int j=1, min=INT_MAX; j<=N; j++) {
            if (!hash[j] && dis[j]<min) {
                min = dis[j];
                now = j;
            }
        }
        hash[now] = 1;
        sum += dis[now];
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    int casen = 1;
    while (scanf("%d", &N), N) {
        for (int i=1; i<=N; i++) {
            scanf("%lf%lf", &cities[i].x, &cities[i].y);
        }
        for (int i=1; i<=N; i++) {
            for (int j=i+1; j<=N; j++) {
                map[i][j] = map[j][i] = distance(i, j);
            }
        }

        double ans = prim();
        if (casen != 1) printf("\n");
        printf("Case #%d:\n", casen++);
        printf("The minimal distance is: %.2lf\n", ans);
    }

    return 0;
}