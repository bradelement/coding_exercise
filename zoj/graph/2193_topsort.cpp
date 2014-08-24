#include "cstdio"
#include "cstring"
#include "queue"
#include "vector"
using namespace std;

char line[16];
int screen[4][4];
vector<int> a[16];
vector<int> g[16];
int du[16];

int id(int i, int j)
{
    return i*4 + j;
}

void f(int i, int j)
{
    int num = i * 3 + j + 1;
    a[id(i, j)].push_back(num);
    a[id(i+1, j)].push_back(num);
    a[id(i, j+1)].push_back(num);
    a[id(i+1, j+1)].push_back(num);
}

void init()
{
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            f(i, j);
        }
    }
}

void build(int num, int i, int j)
{
    vector<int> &v = a[id(i, j)];
    for (int c=0; c<v.size(); c++) {
        if (v[c]!=num) {
            g[num].push_back(v[c]);
        }
    }
}

bool topsort(int n)
{
    memset(du, 0, sizeof(du));
    for (int i=0; i<n; i++) {
        for (int j=0; j<g[i].size(); j++) {
            du[g[i][j]]++;
        }
    }
    int tot = 0;
    queue<int> q;
    for (int i=0; i<n; i++) {
        if (!du[i]) q.push(i);
    }
    while (!q.empty()) {
        int x = q.front(); q.pop();
        tot++;
        for (int i=0; i<g[x].size(); i++) {
            int t = g[x][i];
            if (--du[t] == 0) q.push(t);
        }
    }

    return tot == n;
}

int main(int argc, char const *argv[])
{
    init();
    while (scanf("%s", line), strcmp(line, "ENDOFINPUT")) {
        for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++) {
                scanf("%d", &screen[i][j]);
            }
        }
        scanf("%s", line);
        for (int i=0; i<16; i++) {
            g[i].clear();
        }

        for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++) {
                build(screen[i][j], i, j);
            }
        }

        puts(topsort(16) ? "THESE WINDOWS ARE CLEAN" : \
            "THESE WINDOWS ARE BROKEN");
    }
    return 0;
}
