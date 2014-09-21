#include "cstdio"
#include "cstring"

const int MAXN = 20;
const int OFFSET = 7;
char grid[MAXN][MAXN];
int R, C;
char line[512];
int cur;

void spiral(int lx, int ly, int rx, int ry) {
    if (lx > rx || ly > ry) return;
    else if (lx == rx) {
        for (int i=ly; i<=ry; i++) {
            line[cur++] = grid[lx][i];
        }
    }
    else if (ly == ry) {
        for (int i=lx; i<=rx; i++) {
            line[cur++] = grid[i][ly];
        }
    }
    else {
        int curx = lx, cury = ly;
        while (cury < ry) {
            line[cur++] = grid[curx][cury++];
        }
        while (curx < rx) {
            line[cur++] = grid[curx++][cury];
        }
        while (cury > ly) {
            line[cur++] = grid[curx][cury--];
        }
        while (curx > lx) {
            line[cur++] = grid[curx--][cury];
        }
        spiral(lx+1, ly+1, rx-1, ry-1);
    }
}

void gao() {
    for (int i=0; i<R; i++) {
        for (int j=0; j<C; j++) {
            grid[i][j] = line[i*C+j] - OFFSET;
        }
    }

    cur = 0;
    spiral(0, 0, R-1, C-1);
    puts(line);
}

int main(int argc, char const *argv[])
{
    while (scanf("%d%d", &R, &C), R) {
        gets(line);
        gets(line);
        gao();
    }
    return 0;
}