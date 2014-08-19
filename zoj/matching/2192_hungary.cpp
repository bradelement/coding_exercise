#include "cstdio"
#include "cstring"
#include "vector"
#include "string"
using namespace std;

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

void add_edge(int a, int b)
{
    g[a].push_back(b);
    g[b].push_back(a);
}

int id(char c)
{
    if (c == 'S') return 0;
    else if (c == 'M') return 1;
    else if (c == 'L') return 2;
    else if (c == 'X') return 3;
    else if (c == 'T') return 4;
}

char line[16];

void input()
{
    for (int i=0; i<MAXN; i++) {
        g[i].clear();
    }

    int cur = 20;
    scanf("%d", &n1);
    vector<string> vs(n1);
    for (int i=0; i<n1; i++) {
        scanf("%s", line);
        vs[i] = line;
    }
    int a[5], b[6];
    scanf("%d%d%d%d%d", &a[0], &a[1], &a[2], &a[3], &a[4]);
    b[0] = 20;
    for (int i=1; i<=5; i++) {
        b[i] = b[i-1] + a[i-1];
    }

    for (int i=0; i<n1; i++) {
        for (int j=id(vs[i][0]); j<=id(vs[i][1]); ++j) {
            for (int k=b[j]; k<b[j+1]; k++) {
                add_edge(i, k);
            }
        }
    }
    scanf("%s", line);
}

int main(int argc, char const *argv[])
{
    while (scanf("%s", line), strcmp(line, "ENDOFINPUT")) {
        input();
        puts(hungary() == n1 ? "T-shirts rock!" : "I'd rather not wear a shirt anyway...");
    }
    return 0;
}