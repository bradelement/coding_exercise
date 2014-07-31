#include "cstdio"
#include "cstring"
#include "iostream"

struct Edge
{
    int start, end, score;
};
const int MAXN = 300;
const int inf = 0x7F7F7F7F;
int P, N, I, F, M;
Edge edges[MAXN*MAXN];
long long dis[MAXN];

void input()
{
    scanf("%d", &N);
    scanf("%d%d", &I, &F);
    scanf("%d", &M);
    int a, b, c;
    for (int i=0; i<M; i++) {
        scanf("%d%d%d", &edges[i].start, &edges[i].end, &edges[i].score);
    }
}
/*
true:  计算出最短路径
false: 有负权回路
*/
bool Bellman_Ford()
{
    std::fill(dis, dis+N, inf);
    dis[I] = 0;
    bool changed;
    for (int i=0; i<N; i++) {
        changed = false;
        for (int j=0; j<M; j++) {
            int start = edges[j].start;
            int end = edges[j].end;
            if (dis[start]+edges[j].score < dis[end]) {
                dis[end] = dis[start]+edges[j].score;
                changed = true;
            }
        }
        if (!changed) return true;
    }
    return false;
}

int main(int argc, char const *argv[])
{
    scanf("%d", &P);
    while (P--) {
        input();
        bool ret = Bellman_Ford();
        if (ret) {
            if (dis[F] == inf) {
                printf("infinity\n");
            }
            else {
                printf("%lld\n", dis[F]);
            }
        }
        else {
            printf("infinity\n");
        }
    }
    return 0;
}