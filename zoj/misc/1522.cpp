#include "cstdio"
#include "cstring"
#include "string"
#include "vector"
using namespace std;

const int MAXN = 21;
vector<int> rel[MAXN];
vector<string> attr[MAXN];
bool vis[MAXN];
int N;
int t1, t2;
char a[3][24];

void send(int p) {
    if (vis[p]) return;
    vis[p] = true;

    if (rel[p].size() < t1) {
        attr[p].push_back(a[0]);
    }
    else if (rel[p].size() < t2) {
        attr[p].push_back(a[1]);
    }
    else {
        attr[p].push_back(a[2]);
    }
    for (int i=0; i<rel[p].size(); i++) {
        send(rel[p][i]);
    }
}

void gao() {
    for (int i=1, t; i<=N; i++) {
        attr[i].clear();
        rel[i].clear();
        while (scanf("%d", &t), t) {
            rel[i].push_back(t);
        }
    }

    int source;
    while (scanf("%d", &source), source) {
        scanf("%d%d%s%s%s", &t1, &t2, a[0], a[1], a[2]);
        memset(vis, 0, sizeof(vis));
        send(source);
        for (int i=1; i<=N; i++) {
            if (!vis[i]) {
                attr[i].push_back(a[0]);
            }
        }
    }

    char name[24];
    for (int i=1; i<=N; i++) {
        scanf("%s", name);
        printf("%s: ", name);
        for (int j=0; j<attr[i].size(); j++) {
            printf("%s ", attr[i][j].c_str());
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    while (scanf("%d", &N), N) {
        gao();
    }    
    return 0;
}