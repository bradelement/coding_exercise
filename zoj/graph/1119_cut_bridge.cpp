#include "cstdio"
#include "cstring"
#include "algorithm"

const int MAXV = 1000;
bool edge[MAXV][MAXV];
int cut[MAXV];
int low[MAXV], dfn[MAXV], vis[MAXV], subnets[MAXV];

int a, b;
//tarjan? - -
void cut_bridge(int cur, int father, int dep, int n) {
    vis[cur] = 1; dfn[cur] = low[cur] = dep;
    int children = 0;

    for (int i=0; i<n; i++) {
        if (edge[cur][i]) {
            if (i != father && vis[i] == 1) {
                if (dfn[i] < low[cur]) {
                    low[cur] = dfn[i];
                }
            }
            if (vis[i] == 0) {
                cut_bridge(i, cur, dep+1, n);
                children++;
                if (low[i] < low[cur]) {
                    low[cur] = low[i];
                }
                if ((father==-1 && children>1) || (father!=-1 && low[i]>=dfn[cur])) {
                    cut[cur] = 1;
                    if (father==-1) {
                        subnets[cur] = children-1;
                    }
                    else {
                        subnets[cur]++;
                    }
                }
                //if (low[i]>dfn[cur]) {
                //    bridge[cur][i] = bridge[i][cur] = 1;
                //}
            }
        }
    }
    vis[cur] = 2;
}

int main(int argc, char const *argv[])
{
    int casen = 1;
    int maxn;
    bool first = true;
    while (scanf("%d", &a), a) {
        maxn = -1;
        maxn = std::max(maxn, a);
        memset(edge, 0, sizeof(edge));
        memset(cut, 0, sizeof(cut));
        memset(subnets, 0, sizeof(subnets));
        memset(vis, 0, sizeof(vis));

        do {
            scanf("%d", &b);
            maxn = std::max(maxn, b);
            a--; b--;
            edge[a][b] = edge[b][a] = 1;
            scanf("%d", &a);
            maxn = std::max(maxn, a);
        } while (a);

        cut_bridge(0, -1, 0, maxn);

        if (!first) {
            printf("\n");
        }
        first = false;
        printf("Network #%d\n", casen++);
        bool flag = false;
        for (int i=0; i<maxn; i++) {
            if (cut[i]) {
                flag = true;
                printf("  SPF node %d leaves %d subnets\n", i+1, subnets[i]+1);
            }
        }
        if (!flag) {
            printf("  No SPF nodes\n");
        }

    }
    return 0;
}