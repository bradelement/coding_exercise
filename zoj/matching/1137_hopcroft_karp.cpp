#include "cstdio"
#include "cstring"
#include "vector"
#include "queue"
using namespace std;

const int MAXN = 1024;
vector<int> g[MAXN];
int mx[MAXN], my[MAXN], dx[MAXN], dy[MAXN], vis[MAXN];
queue<int> que;
int n1;

bool find(int u)
{
    for (int i=0; i<g[u].size(); i++) {
        if (!vis[g[u][i]] && dy[g[u][i]] == dx[u] + 1) {
            vis[g[u][i]] = 1;
            if (!my[g[u][i]] || find(my[g[u][i]])) {
                mx[u] = g[u][i];
                my[g[u][i]] = u;
                return true;
            }
        }
    }
    return false;
}

int hopcroft_karp()
{
    memset(mx, 0, sizeof(mx));
    memset(my, 0, sizeof(my));

    int ans = 0;
    while (1) {
        bool flag = false;
        while (!que.empty()) que.pop();
        memset(dx, 0, sizeof(dx));
        memset(dy, 0, sizeof(dy));
        for (int i=1; i<=n1; i++) {
            if (!mx[i]) que.push(i);
        }
        while (!que.empty()) {
            int u = que.front(); que.pop();
            for (int i=0; i<g[u].size(); i++) {
                if (!dy[g[u][i]]) {
                    dy[g[u][i]] = dx[u] + 1;
                    if (my[g[u][i]]) {
                        dx[my[g[u][i]]] = dy[g[u][i]] + 1;
                        que.push(my[g[u][i]]);
                    }
                    else {
                        flag = true;
                    }
                }
            }
        }
        if (!flag) break;
        memset(vis, 0, sizeof(vis));
        for (int i=1; i<=n1; i++) {
            if (!mx[i] && find(i)) ans++;
        }
    }
    return ans;
}

void input()
{
    for (int i=1; i<=n1; i++) {
        g[i].clear();   
    }
    int no, m;
    for (int i=0; i<n1; i++) {
        scanf("%d: (%d)", &no, &m);
        for (int j=0, tmp; j<m; j++) {
            scanf("%d", &tmp);
            g[no+1].push_back(tmp+1);
        }
    }
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d", &n1)) {
        input();
        printf("%d\n", n1 - hopcroft_karp()/2);
    }
    return 0;
}