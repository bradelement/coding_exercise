#include "cstdio"
#include "vector"

const int MAXN = 101;
int N;
int a[MAXN][MAXN], b[MAXN];
int dp[MAXN][MAXN];
bool vis[MAXN][MAXN][MAXN];

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
            dp[i][j] = a[i][j];
            for (int k=1; k<=N; k++) {
                vis[i][j][k] = false;
            }
        }
    }
}

std::vector<int> gen_path(int from, int to)
{
    if (from == to) {
        std::vector<int> ret;
        ret.push_back(from);
        return ret;
    }
    for (int i=1; i<=N; i++) {
        if (vis[from][to][i]) {
            std::vector<int> p1 = gen_path(from, i);
            std::vector<int> p2 = gen_path(i, to);
            for (int j=1; j<p2.size(); j++) {
                p1.push_back(p2[j]);
            }
            return p1;
        }
    }
    std::vector<int> ret;
    ret.push_back(from);
    ret.push_back(to);
    return ret;
}

void floyd()
{
    int tmp;
    for (int k=1; k<=N; k++) {
        for (int i=1; i<=N; i++) {
            for (int j=1; j<=N; j++) {
                if (i!=j && dp[i][k] > 0 && dp[k][j] > 0) {
                    tmp = dp[i][k] + dp[k][j] + b[k];
                    if (dp[i][j] == -1 || tmp < dp[i][j]) {
                        for (int kk=1; kk<k; kk++) {
                            vis[i][j][kk] = false;
                        }
                        dp[i][j] = tmp;
                        vis[i][j][k] = true;
                    }
                    else if (tmp == dp[i][j]) {
                        std::vector<int> oripath = gen_path(i, j);
                        int orik = 0;
                        for (int kk=1; kk<k; kk++) {
                            if (vis[i][j][kk]) {
                                vis[i][j][kk] = false;
                                orik = kk;
                                break;
                            }
                        }
                        vis[i][j][k] = true;
                        std::vector<int> newpath = gen_path(i, j);
                        if (oripath < newpath) {
                            vis[i][j][k] = false;
                            if (orik) vis[i][j][orik] = true;
                        }
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