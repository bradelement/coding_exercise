#include "cstdio"
#include "cstring"
#include "queue"

const int MAXN = 1024;
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

    scanf("%d", &n);
    for (int i=1, p; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            scanf("%d", &p);
            pref[i][j] = p;
        }
        next[i] = 1;
        future_wife[i] = 0;
        q.push(i);
    }
    for (int i=1, p; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            scanf("%d", &p);
            order[i][p] = j;
        }
        future_husband[i] = 0;
    }
}

void output()
{
    for (int i=1; i<=n; i++) {
        printf("%d\n", future_wife[i]);
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
    }
    return 0;
}