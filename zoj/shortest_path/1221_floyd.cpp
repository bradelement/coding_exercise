#include "cstdio"
#include "cstring"

const int MAXN = 20;
int n, m;
int dp[MAXN+1][MAXN+1];

void floyd()
{
    int tmp;
    for (int k=1; k<=MAXN; k++) {
        for (int i=1; i<=MAXN; i++) {
            if (dp[i][k] >= 0) {
                for (int j=1; j<=MAXN; j++) {
                    if (dp[k][j] >= 0) {
                        tmp = dp[i][k] + dp[k][j];
                        if (dp[i][j] == -1) {
                            dp[i][j] = tmp;
                        }
                        else if (tmp < dp[i][j]) {
                            dp[i][j] = tmp;
                        }
                    }
                }
            }
        }
    }
}

void input()
{
    memset(dp, -1, sizeof(dp));
    for (int i=0; i<n; i++) {
        scanf("%d", &m);
        dp[1][m] = dp[m][1] = 1;
    }
    for (int i=2; i<=19; i++) {
        scanf("%d", &n);
        for (int j=0; j<n; j++) {
            scanf("%d", &m);
            dp[i][m] = dp[m][i] = 1;
        }
    }
}
void gao(int casen)
{
    scanf("%d", &n);
    int a, b;
    printf("Test Set #%d\n", casen);
    for (int i=0; i<n; i++) {
        scanf("%d%d", &a, &b);
        printf("%d to %d: %d\n", a, b, dp[a][b]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    int casen = 1;
    while (~scanf("%d", &n)) {
        input();
        floyd();
        gao(casen++);
    }
    return 0;
}