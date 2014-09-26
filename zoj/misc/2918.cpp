#include "cstdio"

const int MAXN = 101;
int h, w;
char grid[MAXN][MAXN];
double dp[MAXN][MAXN];

double cal(int x, int y) {
    if (y<0 || y>=w) return 0;
    if (dp[x][y] >= 0) return dp[x][y];
    double ret = 0;
    for (int i=x; i<h; i++) {
        if (grid[i][y] >= '1' && grid[i][y] <= '9') {
            ret = grid[i][y] - '0';
            break;
        }
        else if (grid[i][y] == '*') {
            ret = (cal(i, y-1) + cal(i, y+1)) / 2;
            break;
        }
    }
    return dp[x][y] = ret;
}

int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &h, &w);
        gets(grid[0]);
        for (int i=0; i<h; i++) {
            gets(grid[i]);
            for (int j=0; j<w; j++) {
                dp[i][j] = -1;
            }
        }

        double ans = -1;
        for (int i=0; i<w; i++) {
            double tmp = cal(0, i);
            if (tmp > ans) ans = tmp;
        }
        printf("%.6lf\n", ans);
    }
    return 0;
}