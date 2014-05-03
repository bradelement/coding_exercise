#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int inf = 0x12345678;
const int MAX_VALUE = 10001;
int V;
int coins[5];
int values[5] = {0, 1, 5, 10, 25};
int dp[MAX_VALUE];
int rec[5][MAX_VALUE];

void ZeroOnePack(int ind, int F, int C, int W) {
    F = min(F, V);
    for (int v=F; v>=C; v--) {
        if (dp[v-C] != -inf && dp[v-C]+W > dp[v]) {
            dp[v] = dp[v-C]+W;
            rec[ind][v] += rec[ind][v-C]+W;
        }
    }
}

void CompletePack(int ind, int F, int C, int W) {
    F = min(F, V);
    for (int v=C; v<=F; v++) {
        if (dp[v-C] != -inf && dp[v-C]+W > dp[v]) {
            dp[v] = dp[v-C]+W;
            rec[ind][v] = rec[ind][v-C] + W;
        }
    }
}

void MultiPack(int ind, int F, int C, int W, int M) {
    if (C*M >= F) {
        CompletePack(ind, F, C, W);
        return;
    }
    int k = 1;
    while (k < M) {
        ZeroOnePack(ind, F, k*C, k*W);
        M -= k;
        k *= 2;
    }
    ZeroOnePack(ind, F, M*C, M*W);
}

void gao() {
    memset(dp, 0, sizeof(dp));
    memset(rec, 0, sizeof(rec));
    for (int j=1; j<=V; j++) {
        dp[j] = -inf;
    }

    for (int i=1; i<=4; i++) {
        MultiPack(i, V, values[i], 1, coins[i]);
    }
    if (dp[V] <= 0) {
        printf("Charlie cannot buy coffee.\n");
        return;
    }
    //printf("dp[%d] is %d\n", V, dp[V]);

    int ans[5];
    int v = V;
    for (int i=4; i>=1; i--) {
        ans[i] = rec[i][v];
        //printf("rec[%d][%d] is %d\n", i, v, rec[i][v]);
        v -= ans[i] * values[i];
    }
    printf("Throw in %d cents, %d nickels, %d dimes, and %d quarters.\n", ans[1], ans[2], ans[3], ans[4]);
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d", &V)) {
        for (int i=1; i<=4; i++) {
            scanf("%d", &coins[i]);
        }
        if (V+coins[1]+coins[2]+coins[3]+coins[4] == 0) break;
        gao();
    }

    return 0;
}