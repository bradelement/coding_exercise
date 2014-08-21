#include "cstdio"
#include "cstring"
#include "queue"

const int MAXN = 32;
//pref  编号为i的男士第j喜欢的人
//order 在编号为i的女士心中，编号为j的男士的排名
//next  男士接下来向谁求婚
int pref[MAXN][MAXN], order[MAXN][MAXN], next[MAXN];
int future_husband[MAXN], future_wife[MAXN];
std::queue<int> q;
int n;

void engage(int man, int woman)
{
    int m = future_husband[woman];
    if (m) {//女士现有的未婚夫
        future_wife[m] = 0; //抛弃m...
        q.push(m);          //m变成未engage
    }
    future_wife[man] = woman;
    future_husband[woman] = man;
}

void stable_marriage()
{
    while (!q.empty()) {
        int man = q.front(); q.pop();
        int woman = pref[man][next[man]++];
        if (!future_husband[woman]) {
            engage(man, woman);
        }
        else if (order[woman][man] < order[woman][future_husband[woman]]) {
            engage(man, woman);
        }
        else {
            q.push(man);
        }
    }
}

void input()
{
    while (!q.empty()) q.pop();
    char line[MAXN];
    scanf("%d", &n);
    for (int i=0; i<2*n; i++) {
        scanf("%s", line);
    }
    for (int i=0; i<n; i++) {
        scanf("%s", line);
        int len = strlen(line);
        int p = line[0] - 'a' + 1;
        for (int j=2; j<len; j++) {
            pref[p][j-1] = line[j] - 'A' + 1;
        }
        next[p] = 1;
        future_wife[p] = 0;
        q.push(p);
    }
    for (int i=0; i<n; i++) {
        scanf("%s", line);
        int len = strlen(line);
        int p = line[0] - 'A' + 1;
        for (int j=2; j<len; j++) {
            order[p][line[j] - 'a' + 1] = j-1;
        }
        future_husband[p] = 0;
    }
}

void output()
{
    for (int i=1; i<=n; i++) {
        printf("%c %c\n", 'a'-1+i, future_wife[i]-1+'A');
    }
}

int main(int argc, char const *argv[])
{
    int casen;
    scanf("%d", &casen);
    for (int ci=1; ci<=casen; ci++) {
        input();
        stable_marriage();
        output();
        if (ci != casen) printf("\n");
    }
    return 0;
}