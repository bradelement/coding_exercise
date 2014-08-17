#include "cstdio"
#include "cstring"
#include "vector"
using namespace std;

const int MAXN = 512;
vector<int> g[MAXN];
int from[MAXN], used[MAXN];
int P, N;

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
    for (int i=0; i<P; i++) {
        memset(used, 0, sizeof(used));
        if (match(i)) {
            ret++;
        }
    }
    return ret;
}

void input()
{
    scanf("%d%d", &P, &N);
    for (int i=0; i<P+N; i++) {
        g[i].clear();
    }
    int n, m;
    for (int i=0; i<P; i++) {
        scanf("%d", &n);
        for (int j=0; j<n; j++) {
            scanf("%d", &m);
            m += P-1;
            g[i].push_back(m);
            g[m].push_back(i);
        }
    }
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--) {
        input();
        puts(hungary() == P ? "YES" : "NO");
    }
    return 0;
}