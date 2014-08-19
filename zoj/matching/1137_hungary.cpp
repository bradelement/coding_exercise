#include "cstdio"
#include "cstring"
#include "vector"
#include "algorithm"
using namespace std;

//二分图最大独立集 = V - 最大匹配
const int MAXN = 1024;
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
    fill(from, from+n1, -1);
    for (int i=0; i<n1; i++) {
        fill(used, used+n1, 0);
        if (match(i)) {
            ret++;
        }
    }
    return ret;
}

void input()
{
    for (int i=0; i<n1; i++) {
        g[i].clear();   
    }
    int no, m;
    for (int i=0; i<n1; i++) {
        scanf("%d: (%d)", &no, &m);
        for (int j=0, tmp; j<m; j++) {
            scanf("%d", &tmp);
            g[no].push_back(tmp);
        }
    }
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d", &n1)) {
        input();
        printf("%d\n", n1 - hungary()/2);
    }

    return 0;
}