#include "cstdio"
#include "cmath"

const int MAXN = 1<<8;
int n;
int rank[MAXN];
int dp[MAXN][MAXN];

void input()
{
    int lim = 1<<n;
    for (int i=0; i<lim; i++) {
        rank[i] = i+1;
    }
    for (int i=1; i<=lim; i++) {
        for (int j=1; j<=lim; j++) {
            dp[i][j] = 0;
        }
    }

    int tmp, other;
    for (int i=n-1; i>=0; i--) {
        lim = 1<<i;
        for (int j=0; j<lim; j++) {
            scanf("%d", &tmp);
            other = rank[2*j] + rank[2*j+1] - tmp;
            dp[tmp][other] = 1;
            rank[j] = tmp;
        }
    }
}

void floyd()
{
    int lim = 1<<n;
    for (int k=1; k<=lim; k++) {
        for (int i=1; i<=lim; i++) {
            for (int j=1; j<=lim; j++) {
                if (dp[i][k] && dp[k][j]) {
                    dp[i][j] = 1;
                }
            }
        }
    }
}

void gao()
{
    int m, p;
    int lim = 1<<n;
    scanf("%d", &m);
    while (m--) {
        scanf("%d", &p);
        int high = 0, low = 0;
        for (int i=1; i<=lim; i++) {
            if (dp[i][p] == 1) {
                high++;
            }
            if (dp[p][i] == 1) {
                low++;
            }
        }
        printf("Player %d can be ranked as high as %d or as low as %d.\n", p, high+1, lim-low);
    }
}

int main(int argc, char const *argv[])
{
    bool first = true;
    while (scanf("%d", &n), n) {
        if (first) first = false;
        else printf("\n");
        input();
        floyd();
        gao();
    }
    return 0;
}