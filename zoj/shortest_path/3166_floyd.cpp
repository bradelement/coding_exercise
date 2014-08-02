#include "cstdio"
#include "cstring"
#include "algorithm"

const int MAXN = 101;
const int inf = 0x3f3f3f3f;
int N, C, M;
int hotels[MAXN];
int dp[MAXN][MAXN];

void input()
{
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=N; j++) {
            dp[i][j] = inf;
        }
    }

    for (int i=0; i<C; i++) {
        scanf("%d", &hotels[i]);
    }

    scanf("%d", &M);
    int a, b, d;
    for (int i=0; i<M; i++) {
        scanf("%d%d%d", &a, &b, &d);
        dp[a][b] = d;
    }
}

void floyd()
{
    int tmp;
    for (int k=1; k<=N; k++) {
        for (int i=1; i<=N; i++) {
            for (int j=1; j<=N; j++) {
                tmp = dp[i][k] + dp[k][j];
                if (tmp < dp[i][j]) dp[i][j] = tmp;
            }
        }
    }
}

void output()
{
    int min_dis = inf, min_idx;
    for (int i=0; i<C; i++) {
        if (dp[hotels[i]][hotels[i]] < min_dis) {
            min_dis = dp[hotels[i]][hotels[i]];
            min_idx = hotels[i];
        }
    }
    if (min_dis == inf) {
        printf("I will nerver go to that city!\n");
    }
    else {
        printf("%d\n", min_idx);
    }
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d", &N, &C)) {
        input();
        floyd();
        output();
    }
    return 0;
}