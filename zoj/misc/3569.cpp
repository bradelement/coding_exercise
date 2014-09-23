#include "cstdio"
#include "cstring"

const int MAXN = 10;
int n, m, t;
int grid[MAXN][MAXN];
struct Plant
{
    int c, b, a;
};
const int MAXT = 30;
Plant plants[MAXT];
int count[MAXT];

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d%d", &n, &m, &t)) {
        for (int i=0; i<t; i++) {
            scanf("%d%d%d", &plants[i].c, &plants[i].b, &plants[i].a);
        }
        int cur = 0;
        for (int j=0; j<m; j++) {
            for (int i=0; i<n; i++) {
                if (plants[cur].c) {
                    grid[i][j] = cur;
                }
                else {
                    grid[i][j] = ++cur;
                }
                plants[cur].c--;
            }
        }

        int angry = 0;
        for (int i=0; i<n; i++) {
            memset(count, 0, sizeof(count));
            for (int j=0; j<m; j++) {
                count[grid[i][j]]++;
            }
            for (int j=0; j<t; j++) {
                if (count[j] > plants[j].b) {
                    angry += (count[j] - plants[j].b) * plants[j].a;
                }
            }
        }
        printf("%.3lf\n", angry * 1.0 / n);
    }
    return 0;
}