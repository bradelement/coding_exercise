#include "cstdio"
#include "cstring"
#include "vector"
using namespace std;

//最小点覆盖.. 官方做法都是树状dp 和 二分图匹配。。。。以后学习。。
//dfs贪心应该是对的 - -

const int MAXN = 1536;
vector<int> edges[MAXN];
bool vis[MAXN];
bool color[MAXN];
int ans;

//注意判断标记vis的顺序- -..
void dfs(int idx) {
    vis[idx] = true;

    for (int i=0; i<edges[idx].size(); i++) {
        if (vis[edges[idx][i]]) continue;

        dfs(edges[idx][i]);
        if (!color[edges[idx][i]]) {
            color[idx] = true;
        }
    }
    if (color[idx]) ans++;
}

int main(int argc, char const *argv[])
{
    int N;
    while (~scanf("%d", &N)) {
        for (int i=0; i<N; i++) {
            edges[i].clear();
        }
        memset(vis, 0, sizeof(vis));
        memset(color, 0, sizeof(color));
        ans = 0;

        for (int i=0, x, num, y; i<N; i++) {
            scanf("%d:(%d)", &x, &num);
            for (int j=0; j<num; j++) {
                scanf("%d", &y);
                edges[x].push_back(y);
                edges[y].push_back(x);
            }
        }

        dfs(0);
        printf("%d\n", ans);
    }
    return 0;
}
