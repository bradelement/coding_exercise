#include "cstdio"
#include "cstring"
#include "vector"
#include "algorithm"
using namespace std;

const int MAXN = 1024;
int N, M;
vector<int> G[MAXN];
int d[MAXN];
bool vis[MAXN];

void input()
{
    for (int i=0; i<N; i++) {
        G[i].clear();
    }
    int a, b;
    for (int i=0; i<M; i++) {
        scanf("%d%d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }
}

void dfs(int idx, int dis)
{
    if (vis[idx]) return;
    vis[idx] = true;
    d[idx] = dis;
    for (int i=0; i<G[idx].size(); i++) {
        dfs(G[idx][i], dis+1);
    }
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d", &N, &M)) {
        input();
        memset(vis, 0, sizeof(vis));
        dfs(0, 1);
        int u = max_element(d, d+N) - d;
        memset(vis, 0, sizeof(vis));
        dfs(u, 1);
        int diameter = *max_element(d, d+N);

        if (diameter > 7) {
            printf("%d\n", diameter);
        }
        else {
            puts("Impossible");
        }
    }
    return 0;
}