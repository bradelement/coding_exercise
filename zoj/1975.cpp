#include "cstdio"
#include "cmath"
#include "iostream"
#include "string"
#include "cstdlib"
#include "cstring"
#include "vector"
#include "set"
#include "map"
#include "algorithm"
using namespace std;

const int MAXN = 1<<11;
char tri[MAXN][MAXN];

void mycopy(int height, int width, int sx, int sy, int x, int y) {
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            tri[x+i][y+j] = tri[sx+i][sy+j]; 
        }
    }
}

void gao() {
    memset(tri, ' ', sizeof(tri));

    tri[0][MAXN/2 - 1] = '/'; tri[0][MAXN/2] = '\\';
    tri[1][MAXN/2 - 2] = '/';
    tri[1][MAXN/2 - 1] = tri[1][MAXN/2] = '_';
    tri[1][MAXN/2 + 1] = '\\';

    for (int i=2; i<=10; i++) {
        mycopy(pow(2, i-1), pow(2, i), 0, MAXN/2 - pow(2, i-1), pow(2, i-1), MAXN/2 - pow(2, i));
        mycopy(pow(2, i-1), pow(2, i), 0, MAXN/2 - pow(2, i-1), pow(2, i-1), MAXN/2);
    }

}

int main(int argc, char const *argv[])
{
    gao();
    int n;
    while (scanf("%d", &n), n) {
        int width = pow(2, n);
        for (int i=0; i<width; i++) {
            int lim = MAXN/2+width-1;
            while (lim>=0 && tri[i][lim] == ' ') lim--;
            for (int j=MAXN/2-width; j<=lim; j++) {
                putchar(tri[i][j]);
            }
            putchar('\n');
        }
        printf("\n");
    }

    return 0;
}
