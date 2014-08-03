#include "cstdio"
#include "algorithm"

const int MAXN = 101;
const int inf = 23333;
int n;
int dp[MAXN][MAXN];

void input()
{
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            dp[i][j] = (i==j ? 0 : inf);
        }
    }

    int m, end, len;
    for (int i=1; i<=n; i++) {
        scanf("%d", &m);
        for (int j=0; j<m; j++) {
            scanf("%d%d", &end, &len);
            dp[i][end] = len;
        }
    }
}

void floyd()
{
    int tmp;
    for (int k=1; k<=n; k++) {
        for (int i=1; i<=n; i++) {
            if (dp[i][k] != inf) {
                for (int j=1; j<=n; j++) {
                    if (dp[k][j] != inf) {
                        tmp = dp[i][k] + dp[k][j];
                        if (tmp < dp[i][j]) dp[i][j] = tmp;
                    }
                }
            }
        }
    }
}

void output()
{
    int maxt = inf, maxi=1;
    int t;
    for (int i=1; i<=n; i++) {
        t = *std::max_element(dp[i]+1, dp[i]+n+1);
        if (t < maxt) {
            maxt = t;
            maxi = i;
        }
    }
    printf("%d %d\n", maxi, maxt);
}

int main(int argc, char const *argv[])
{
    while (scanf("%d", &n), n) {
        input();
        floyd();
        output();
    }
    return 0;
}