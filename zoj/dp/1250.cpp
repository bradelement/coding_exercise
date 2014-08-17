#include "cstdio"
#include "cstring"
#include "vector"

const int MAXN = 11;
const int MAXK = 1001;

int n, k;
std::vector<int> flight[MAXN][MAXN];
int dp[MAXK][MAXN];

void input()
{
    int d;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            if (i == j) continue;
            flight[i][j].clear();

            scanf("%d", &d);
            for (int k=0, tmp; k<d; k++) {
                scanf("%d", &tmp);
                flight[i][j].push_back(tmp);
            }
        }
    }
}

int gao()
{
    memset(dp, -1, sizeof(dp));
    dp[0][1] = 0;

    for (int day=1; day<=k; day++) {
        for (int to=1; to<=n; to++) {
            for (int from=1; from<=n; from++) {
                if (to == from || dp[day-1][from] == -1) continue;
                int p = (day-1) % flight[from][to].size();
                if (flight[from][to][p]) {
                    if (dp[day][to] == -1) {
                        dp[day][to] = dp[day-1][from] + flight[from][to][p];
                    }
                    else {
                        dp[day][to] = std::min(dp[day][to], dp[day-1][from] + flight[from][to][p]);
                    }
                }
            }
        }
    }

    return dp[k][n];
}

void output(int casen, int ans)
{
    printf("Scenario #%d\n", casen);
    if (ans == -1) {
        printf("No flight possible.\n");
    }
    else {
        printf("The best flight costs %d.\n", ans);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    int casen = 1;
    while (scanf("%d%d", &n, &k), n) {
        input();
        int ret = gao();
        output(casen++, ret);
    }
    return 0;
}