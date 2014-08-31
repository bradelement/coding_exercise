#include <cstdio>
#include <cstring>

const int MAXL = 128;
int l;
char puzzle[MAXL][MAXL];
char line[MAXL];
int slen;

int sx[] = {0, -1, -1, -1, 0, 1, 1, 1};
int sy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

bool valid(int x, int y)
{
    return x>=0 && x<l && y>=0 && y<l;
}

bool _search(int x, int y)
{
    int nx, ny;
    for (int i=0; i<8; i++) {
        nx = x; ny = y;
        int cur = 0;
        while (valid(nx, ny) && puzzle[nx][ny] == line[cur]) {          
            if (cur == slen-1) {
                printf("%d,%d %d,%d\n", x+1, y+1, nx+1, ny+1);
                return true;
            }
            nx += sx[i];
            ny += sy[i];
            cur++;
        }
    }
    return false;
}

void search()
{
    for (int i=0; i<l; i++) {
        for (int j=0; j<l; j++) {
            if (_search(i, j)) {
                return;
            }
        }
    }
    puts("Not found");
}

void gao()
{
    scanf("%d", &l);
    gets(puzzle[0]);
    for (int i=0; i<l; i++) {
        gets(puzzle[i]);
    }
    while (gets(line), strcmp(line, "0")) {
        slen = strlen(line);
        search();
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    for (int ci=1; ci<=N; ci++) {
        gao();
        if (ci != N) printf("\n");
    }

    return 0;
}