#include "cstdio"
#include "vector"

const int MAXN = 101;
const int inf = 0x3f3f3f3f;
int N;
int a[MAXN][MAXN], b[MAXN];
int dp[MAXN][MAXN], path[MAXN][MAXN];

void input()
{
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=N; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i=1; i<=N; i++) {
        scanf("%d", &b[i]);
    }
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=N; j++) {
            dp[i][j] = (a[i][j] == -1 ? inf : a[i][j]);
            path[i][j] = j;
        }
    }
}

std::vector<int> gen_path(int from, int to)
{
    std::vector<int> ret;
    int cur = from;
    ret.push_back(from);
    while (cur != to) {
        cur = path[cur][to];
        ret.push_back(cur);
    }
    return ret;
}

void floyd()
{
    int tmp;
    for (int k=1; k<=N; k++) {
        for (int i=1; i<=N; i++) {
            for (int j=1; j<=N; j++) {
                tmp = dp[i][k] + dp[k][j] + b[k];
                if (tmp < dp[i][j]) {
                    dp[i][j] = tmp;
                    path[i][j] = path[i][k];
                }
                else if (tmp == dp[i][j]) {
                    if (path[i][k] < path[i][j]) {
                        path[i][j] = path[i][k];
                    }
                }   
            }
        }
    }
}

void gao()
{
    int from, to;
    while (scanf("%d%d", &from, &to), from!=-1) {
        printf("From %d to %d :\n", from, to);
        printf("Path: ");
        std::vector<int> path = gen_path(from, to);
        for (int i=0; i<path.size(); i++) {
            if (i) printf("-->");
            printf("%d", path[i]);
        }
        printf("\nTotal cost : %d\n\n", dp[from][to]);
    }
}

int main(int argc, char const *argv[])
{
    while (scanf("%d", &N), N) {
        input();
        floyd();
        gao();
    }
    return 0;
}