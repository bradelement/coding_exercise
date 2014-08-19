#include "cstdio"
#include "cstring"
#include "vector"
#include "string"
using namespace std;

const int MAXN = 200;
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

void add_edge(int a, int b)
{
    g[a].push_back(b);
    g[b].push_back(a);
}

int n, m, k;

void input()
{
    for (int i=0; i<MAXN; i++) {
        g[i].clear();
    }
    scanf("%d%d", &m, &k);
    int a, b, c;
    for (int i=0; i<k; i++) {
        scanf("%d%d%d", &a, &b, &c);
        if (b == 0 || c == 0) continue;
        add_edge(b, n+c);
    }
    n1 = n;
}

int main(int argc, char const *argv[])
{
    while (scanf("%d", &n), n) {
        input();
        printf("%d\n", hungary());
    }
    return 0;
}