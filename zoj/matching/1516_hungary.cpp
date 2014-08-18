#include "cstdio"
#include "cstring"
#include "vector"
using namespace std;

const int MAXN = 128;
vector<int> g[MAXN];
int from[MAXN], used[MAXN];
int n1;

bool match(int x)
{
    for (int i=0; i<g[x].size(); i++) {
        if (!used[g[x][i]]) {
            used[g[x][i]] = 1;
            if (from[g[x][i]] == -1 || match(from[g[x][i]])) {
                from[g[x][i]] = x;
                return true;
            }
        }
    }
    return false;
}

int hungary()
{
    int ret = 0;
    memset(from, -1, sizeof(from));
    for (int i=0; i<n1; i++) {
        memset(used, 0, sizeof(used));
        if (match(i)) {
            ret++;
        }
    }
    return ret;
}

int N, M, K;
int land[101][101];
int sx[4] = {1, -1, 0, 0};
int sy[4] = {0, 0, 1, -1};

bool valid(int x, int y)
{
    return x>=1 && x<=N && y>=1 && y<=M && land[x][y] >= 0;
}

void input()
{
    for (int i=0; i<MAXN; i++) {
        g[i].clear();
    }
    memset(land, 0, sizeof(land));
    scanf("%d", &K);
    int x, y;
    for (int i=0; i<K; i++) {
        scanf("%d%d", &x, &y);
        land[x][y] = -1;
    }

    int left = 0, right = 60;
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=M; j++) {
            if (land[i][j] < 0) continue;
            if ((i+j) & 1) {//black
                for (int k=0; k<4; k++) {
                    int ii = i + sx[k];
                    int jj = j + sy[k];
                    if (valid(ii, jj)) {
                        if (land[ii][jj] == 0) {
                            land[ii][jj] = right++;
                        }
                        g[left].push_back(land[ii][jj]);
                        g[land[ii][jj]].push_back(left);
                    }
                }
                left++;
            }
        }
    }

    n1 = left;
}

int main(int argc, char const *argv[])
{
    while (scanf("%d%d", &N, &M), N) {
        input();
        printf("%d\n", hungary());
    }
    return 0;
}