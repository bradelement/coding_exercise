#include "cstdio"
#include "cstring"

const int MAXN = 26;
int dp[MAXN][MAXN];
int m;
void input()
{
    char line[8];
    int from, to;
    memset(dp, 0, sizeof(dp));
    scanf("%d", &m);
    for (int i=0; i<m; i++) {
        scanf("%s", line);
        from = line[0] - 'A';
        to   = line[2] - 'A';
        if (line[1] == '<') {
            dp[from][to] = 1;
        }
        else {
            dp[to][from] = 1;
        }
    }
}

void floyd()
{
    for (int k=0; k<MAXN; k++) {
        for (int i=0; i<MAXN; i++) {
            for (int j=0; j<MAXN; j++) {
                if (!dp[i][j] && dp[i][k] && dp[k][j]) {
                    dp[i][j] = 2;
                }
            }
        }
    }
}

void output(int casen)
{
    printf("Case %d:\n", casen);
    bool found = false;
    for (int i=0; i<MAXN; i++) {
        for (int j=0; j<MAXN; j++) {
            if (dp[i][j] == 2) {
                printf("%c<%c\n", i+'A', j+'A');
                found = true;
            }
        }
    }
    if (!found) {
        printf("NONE\n");
    }
}

int main(int argc, char const *argv[])
{
    int casen;
    scanf("%d", &casen);
    for (int ci=1; ci<=casen; ci++) {
        input();
        floyd();
        output(ci);
    }
    return 0;
}