#include "cstdio"

const int MAXN = 101;
char grid[MAXN][MAXN];
char new_grid[MAXN][MAXN];
int r, c, n;

bool valid(int x, int y) {
    return x>=0 && x<r && y>=0 && y<c;
}

bool win(char a, char b) {
    return (a=='R' && b=='S') || (a=='S' && b=='P') || (a=='P' && b=='R');
}

int sx[] = {0, -1, 0, 1};
int sy[] = {-1, 0, 1, 0};

void gao(int x, int y) {
    for (int i=0; i<4; i++) {
        int nx = x + sx[i];
        int ny = y + sy[i];
        if (valid(nx, ny) && win(grid[x][y], grid[nx][ny])) {
            new_grid[nx][ny] = grid[x][y];
        }
    }
}

void gao() {
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            new_grid[i][j] = grid[i][j];
        }
    }
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            gao(i, j);
        }
    }
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            grid[i][j] = new_grid[i][j];
        }
    }
}

int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    for (int ci=1; ci<=t; ci++) {
        scanf("%d%d%d", &r, &c, &n);
        gets(grid[0]);
        for (int i=0; i<r; i++) {
            gets(grid[i]);
        }
        for (int i=0; i<n; i++) {
            gao();
        }

        for (int i=0; i<r; i++) {
            for (int j=0; j<c; j++) {
                putchar(grid[i][j]);
            }
            putchar('\n');
        }
        if (ci != t) putchar('\n');
    }
    return 0;
}