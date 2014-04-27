#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <cctype>
#include <map>
#include <iomanip>
#include <climits>
using namespace std;

const int limit = 100010;

int cash, N;
int n[limit], D[limit];
int dp[limit];

void ZeroOnePack(int V, int C) {
    if (V > limit) V = limit;
    for (int i=V; i>=C; i--) {
        dp[i] |= dp[i-C];
    }
}

void CompletePack(int V, int C) {
    if (V > limit) V = limit;
    for (int i=C; i<=V; i++) {
        dp[i] |= dp[i-C];
    }
}

void MultiplePack(int V, int C, int M) {
    if (C * M >= V) {
        CompletePack(V, C);
        return;
    }
    int k = 1;
    while (k < M) {
        ZeroOnePack(k*V, k*C);
        M -= k;
        k *= 2;
    }
    ZeroOnePack(M*V, M*C);
}

int gao() {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i=1; i<=N; i++) {
        MultiplePack(cash, D[i], n[i]);
    }

    for (int i=cash; i>=0; i--) {
        if (dp[i]) return i;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d", &cash)) {
        scanf("%d", &N);
        for (int i=1; i<=N; i++) {
            scanf("%d%d", &n[i], &D[i]);
        }
        int ret;
        if (cash == 0 || N == 0) {
            ret = 0;
        }
        else {
            ret = gao();
        }
        printf("%d\n", ret);
    }

    return 0;
}
