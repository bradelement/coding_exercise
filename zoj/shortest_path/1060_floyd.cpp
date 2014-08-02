#include "cstdio"
#include "cstring"
#include "string"

const int MAXN = 26;
int dp[MAXN][MAXN];
int n, m;

void floyd()
{
    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            if (dp[i][k]) {
                for (int j=0; j<n; j++) {
                    if (dp[k][j]) {
                        dp[i][j] = 1;
                    }
                }
            }
        }
    }
}

bool ok(std::string &order)
{
    int mi[MAXN] = {0};
    int sum;
    for (int i=0; i<n; i++) {
        sum = 0;
        for (int j=0; j<n; j++) {
            sum += dp[i][j];
        }
        if (mi[sum]) return false;
        mi[sum] = i + 'A';
    }
    
    for (int i=n-1; i>=0; i--) {
        order += mi[i];
    }

    return true;
}

void gao()
{
    memset(dp, 0, sizeof(dp));
    char line[8];
    int from, to, i;
    bool flag = false;
    for (i=0; i<m; i++) {
        scanf("%s", line);
        from = line[0] - 'A'; to = line[2] - 'A';
        if (dp[to][from]) {
            printf("Inconsistency found after %d relations.\n", i+1);
            flag = true;
            break;
        }
        dp[from][to] = 1;
        floyd();
        std::string order;
        if (ok(order)) {
            printf("Sorted sequence determined after %d relations: %s.\n", i+1, order.c_str());
            flag = true;
            break;
        }
    }
    for (int j=i+1; j<m; j++) {
        scanf("%s", line);
    }
    if (!flag) {
        printf("Sorted sequence cannot be determined.\n");
    }
}

int main(int argc, char const *argv[])
{
    while (scanf("%d%d", &n, &m), n) {
        gao();
    }
    return 0;
}