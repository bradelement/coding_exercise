#include "cstdio"
#include "cmath"
#include "climits"
#include "cstring"

const int MAXN = 1001;
int N;

int adapter[MAXN];
int map[MAXN][MAXN];
int dis[MAXN];
int hash[MAXN];

int prim()
{
    int sum = 0;
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
    int casen;
    scanf("%d", &casen);
    while (casen--) {
        scanf("%d", &N);
        for (int i=1; i<=N; i++) {
            scanf("%d", &adapter[i]);
        }
        for (int i=1; i<=N; i++) {
            for (int j=1; j<=N; j++) {
                scanf("%d", &map[i][j]);
                map[i][j] += adapter[i]+adapter[j];
            }
        }

        int ans = prim();
        printf("%d\n", ans);
    }

    return 0;
}