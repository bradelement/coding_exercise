#include "cstdio"

const int MAXN = 100;
int grid[MAXN][MAXN];
const int MAXS = 1024;
int r1[MAXS], r2[MAXS];
char dir[MAXS][2];
int tot;
int M, N;

bool valid(int x, int y) {
    return x>=0 && x<M && y>=0 && y<N;
}
int sx[4] = {-1, 1, 0, 0};
int sy[4] = {0, 0, -1, 1};

bool go(int x, int y, int step) {
    if (step == tot) return true;
    for (int s=r1[step]; s<=r2[step]; s++) {
        int xx = x, yy = y;
        int d;
        switch (dir[step][0]) {
        case 'U':
            d = 0; break;
        case 'D':
            d = 1; break;
        case 'L':
            d = 2; break;
        case 'R':
            d = 3; break;
        }
        for (int j=0; j<s; j++) {
            xx += sx[d];
            yy += sy[d];
            if (!valid(xx, yy) || grid[xx][yy] == 1) return false;
        }
        if (go(xx, yy, step+1)) return true;
    }
    return false;
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &M, &N);
        for (int i=0; i<M; i++) {
            for (int j=0; j<N; j++) {
                scanf("%d", &grid[i][j]);
            }
        }
        tot = 0;
        while (scanf("%d%d", &r1[tot], &r2[tot]), r1[tot]) {
            scanf("%s", dir[tot++]);
        }

        int ans = 0;
        for (int i=0; i<M; i++) {
            for (int j=0; j<N; j++) {
                if (grid[i][j] == 0) {
                    if (go(i, j, 0)) {
                        ans++;
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}