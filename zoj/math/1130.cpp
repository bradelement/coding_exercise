#include "cstdio"
#include "unordered_map"
#include "string"
using namespace std;

int dp[16][1<<15];

void gao() {
    for (int i=1; i<=15; i++) {
        int lim = 1<<i;
        unordered_map<int, int> mii;
        dp[i][0] = 0;
        mii[0] = 1;
        int mask = (1<<i) - 1;
        int value = mask;
        for (int j=0; j<i; j++) {
            dp[i][lim-i+j] = value;
            mii[value] = 1;
            value = (value << 1) & mask; 
        }
        for (int j=1; j<lim-i; j++) {
            value = (dp[i][j-1] << 1) & mask;
            if (mii.find(value) != mii.end()) {
                value++;
            }
            dp[i][j] = value;
            mii[value] = 1;
        }
    }
}

int main(int argc, char const *argv[])
{
    gao();
    int n, k;
    while (scanf("%d%d", &n, &k), n) {
        printf("%d\n", dp[n][k]);
    }
    return 0;
}