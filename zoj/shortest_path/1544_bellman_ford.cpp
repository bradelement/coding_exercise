#include "cstdio"
#include "cstring"
#include "algorithm"

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

bool Bellman_Ford()
{
    std:fill(dis, dis+N, inf);
    dis[I] = 0;
    for (int i=0; i<N-1; i++) {
        for (int j=0; j<M; j++) {
            int start = edges[j].start;
            int end = edges[j].end;
            if (dis[start]+edges[j].score < dis[end]) {
                dis[end] = dis[start]+edges[j].score;
            }
        }
    }
    for (int i=0; i<M; i++) {
        int start = edges[i].start;
        int end = edges[i].end;
        if (dis[start]+edges[i].score < dis[end]) {
            return false;
        }
    }
    return true;
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