const int MAXV = 1000;
int edge[MAXV][MAXV];
int bridge[MAXV][MAXV], cut[MAXV];
int low[MAXV], dfn[MAXV], vis[MAXV];

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
                }
                if (low[i]>dfn[cur]) {
                    bridge[cur][i] = bridge[i][cur] = 1;
                }
            }
        }
    }
    vis[cur] = 2;
}