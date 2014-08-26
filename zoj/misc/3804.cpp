#include "cstdio"
#include "cstring"
#include "algorithm"
using namespace std;

const int MAXN = 52;
char grid[MAXN][MAXN];
char new_grid[MAXN][MAXN];
int Q, N, M, F, K;
int ck;

struct LeavingMsg
{
    int x, y, t;
    bool operator< (const LeavingMsg &other) const {
        return t < other.t;
    }
};
LeavingMsg msg[MAXN * MAXN];

void input()
{
    scanf("%d%d%d%d", &N, &M, &F, &K);
    gets(grid[0]);
    for (int i=1; i<=N; i++) {
        gets(grid[i]+1);
    }
    for (int i=0; i<K; i++) {
        scanf("%d%d%d", &msg[i].t, &msg[i].x, &msg[i].y);
    }
    sort(msg, msg+K);
    ck = 0;
}

inline bool valid(int x, int y)
{
    return x>=1 && x<=N && y>=1 && y<=M;
}

int sx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int sy[] = {0, -1, -1, -1, 0, 1, 1, 1};
inline int icount(int x, int y, char c)
{
    int ret = 0, xx, yy;
    for (int i=0; i<8; i++) {
        xx = x + sx[i];
        yy = y + sy[i];
        if (valid(xx, yy) && grid[xx][yy] == c) ret++;
    }
    return ret;
}

void _change(int x, int y)
{
    if (grid[x][y] == 'X') {//left
        return;
    } else if (grid[x][y] == '1') {//awake
        int anum = icount(x, y, '1');
        if (anum == 2 || anum == 3) {
            new_grid[x][y] = '1';
        }
        else {
            new_grid[x][y] = '0';
        }
    } else if (grid[x][y] == '0') {
        int anum = icount(x, y, '1');
        if (anum == 3) {
            new_grid[x][y] = '1';
        }
        else {
            new_grid[x][y] = '0';
        }
    }
}

void leave(int day)
{
    while (ck < K) {
        if (msg[ck].t == day) {
            new_grid[msg[ck].x][msg[ck].y] = 'X';
            ck++;
            continue;
        }
        else {
            break;
        }
    }
}

void _gao(int day)
{
    /*
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=M; j++) {
            new_grid[i][j] = grid[i][j];
        }
    }*/
    memcpy(new_grid, grid, sizeof(new_grid));
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=M; j++) {
            _change(i, j);
        }
    }
    leave(day);

    /*
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=M; j++) {
            grid[i][j] = new_grid[i][j];
        }
    }*/
    memcpy(grid, new_grid, sizeof(grid));
}

void gao()
{
    for (int day=1; day<=F; day++) {
        _gao(day);    
    }
}

void output()
{
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=M; j++) {
            putchar(grid[i][j]);
        }
        putchar('\n');
    }
}

int main(int argc, char const *argv[])
{
    scanf("%d", &Q);
    while (Q--) {
        input();
        gao();
        output();
    }
    return 0;
}