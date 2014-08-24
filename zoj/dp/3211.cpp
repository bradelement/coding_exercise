#include "cstdio"
#include "cstring"
#include "algorithm"
using namespace std;

const int MAXN = 256;
int n, m;
struct Node
{
    int a, b;
    bool operator< (const Node &other) const {
        return b < other.b;
    }
};
Node node[MAXN];
int dp[MAXN];

void zero_one_pack(int V, int C, int ai, int bi)
{
    for (int v=V, c; v>=C; v--) {
        c = dp[v-C] + ai + bi*(v-1);
        if (c > dp[v]) dp[v] = c;
    }
}

int gao()
{
    scanf("%d%d", &n, &m);
    for (int i=0; i<n; i++) {
        scanf("%d", &node[i].a);
    }
    for (int i=0; i<n; i++) {
        scanf("%d", &node[i].b);
    }
    //b升序保证策略最优
    sort(node, node+n);

    memset(dp, 0, sizeof(dp));

    //01背包
    //n个物品 背包大小为m
    for (int i=0; i<n; i++) {
        zero_one_pack(m, 1, node[i].a, node[i].b);
    }

    return dp[m];
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--) {
        printf("%d\n", gao());
    }
    return 0;
}