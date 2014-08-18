#include "cstdio"
#include "cstring"
#include "vector"
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

int value(char c)
{
    if (c >= '2' && c <= '9') return c - '0';
    else if (c == 'T') return 10;
    else if (c == 'J') return 11;
    else if (c == 'Q') return 12;
    else if (c == 'K') return 13;
    else if (c == 'A') return 14;
}
int suit(char c)
{
    if (c == 'C') return 1;
    else if (c == 'D') return 2;
    else if (c == 'S') return 3;
    else if (c == 'H') return 4;
}

int cal(char *s)
{
    return 10 * value(s[0]) + suit(s[1]);
}

void input()
{
    for (int i=0; i<MAXN; i++) {
        g[i].clear();
    }
    
    int N;
    scanf("%d", &N);
    char card[4];
    vector<int> adam(N);
    for (int i=0; i<N; i++) {
        scanf("%s", card);
        adam[i] = cal(card);
    }
    for (int i=0; i<N; i++) {
        scanf("%s", card);
        int cur = cal(card);
        for (int j=0; j<N; j++) {
            if (cur > adam[j]) {
                add_edge(i, j+N);
            }
        }
    }
    n1 = N;
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--) {
        input();
        printf("%d\n", hungary());
    }

    return 0;
}