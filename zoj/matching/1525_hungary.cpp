#include "cstdio"
#include "cstring"
#include "vector"
using namespace std;

//最小路径覆盖 
//有向图最小路径覆盖为 V - 最大匹配
//无向图最小路径覆盖为 V - 最大匹配/2

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

void input()
{
    for (int i=0; i<MAXN; i++) {
        g[i].clear();
    }
    
    int inter, street;
    scanf("%d%d", &inter, &street);
    int x, y;
    for (int i=0; i<street; i++) {
        scanf("%d%d", &x, &y);
        x--; y--;
        g[x].push_back(y);
    }

    n1 = inter;
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--) {
        input();
        printf("%d\n", n1 - hungary());
    }
    return 0;
}