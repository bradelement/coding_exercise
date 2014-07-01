#include "cstdio"
#include "cstring"

const int MAXN = 22;
char grid[MAXN][MAXN];
int used[MAXN][MAXN];
int n, m;

void print_grid() {
    printf("----------\n");
    for (int i=0; i<n; i++) {
        puts(grid[i]);
    }
    printf("----------\n");
}

int dfs(int x, int y, char c) {
    if (x<0 || x>=n || y<0 || y>=m || used[x][y] || grid[x][y] != c) return 0;

    used[x][y] = 1;
    return 1 + dfs(x-1, y, c) + dfs(x+1, y, c) + \
        dfs(x, y-1, c) + dfs(x, y+1, c);
}

int check_block(int &x, int &y) {
    x = y = -1;
    int max_block = 1;
    memset(used, 0, sizeof(used));
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (!used[i][j] && grid[i][j]!='0') {
                int tmp = dfs(i, j, grid[i][j]);
                if (tmp > max_block) {
                    x = i; y = j;
                    max_block = tmp;
                }
            }
        }
    }

    return max_block;
}

void del(int x, int y, char c) {
    if (x<0 || x>=n || y<0 || y>=m || grid[x][y] != c) return;

    grid[x][y] = '0';
    del(x+1, y, c);
    del(x-1, y, c);
    del(x, y+1, c);
    del(x, y-1, c); 
}

void move() {
    int cur_col = 0;
    for (int j=0; j<m; j++) {
        int cur_row = n - 1;
        bool empty = true;
        for (int i=n-1; i>=0; i--) {
            if (grid[i][j] != '0') {
                empty = false;
                grid[cur_row--][cur_col] = grid[i][j];
            }
        }
        for (int i=0; i<=cur_row; i++) {
            grid[i][cur_col] = '0';
        }
        if (!empty) {
            cur_col++;
        }
    }
    for (int j=cur_col; j<m; j++) {
        for (int i=0; i<n; i++) {
            grid[i][j] = '0';
        }
    }
}

int gao() {
    int ret = 0;
    int x, y, tmp;
    while (1) {
        tmp = check_block(x, y);
        if (tmp == 1) break;

        ret += tmp * (tmp-1);
        del(x, y, grid[x][y]);
        move();
        //print_grid();
    }

    return ret;
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d", &n, &m)) {
        gets(grid[0]);
        for (int i=0; i<n; i++) {
            gets(grid[i]);
        }

        printf("%d\n", gao());
    }
    return 0;
}
