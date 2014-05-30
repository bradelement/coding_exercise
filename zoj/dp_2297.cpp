#include "iostream"
#include "stack"
#include "cstdio"
#include "cstring"
using namespace std;

const int MAXN = 19;
int dp[1<<MAXN];
int c[MAXN], r[MAXN];
int boss;

int main(int argc, char const *argv[])
{
    int n;
    while (~scanf("%d", &n)) {
        n--;
        for (int i=0; i<n; i++) {
            scanf("%d%d", &c[i], &r[i]);
        }
        scanf("%d", &boss);

        unsigned int lim = 1<<n;
        unsigned int s;
        memset(dp, 0, lim*sizeof(int));
        dp[0] = 100;
        
        for (unsigned i=1; i<lim; i++) {
            for (int j=0; j<n; j++) {
                if (i & (1<<j)) {
                    s = i & ~(1<<j);
                    if (dp[s] >= c[j]) {
                        dp[i] = max(dp[i], dp[s]-c[j]+r[j]);
                        if (dp[i] > 100) dp[i] = 100; 
                    }
                }
            }
        }
        if (dp[lim-1] >= boss) {
            puts("clear!!!");
        }
        else {
            puts("try again");
        }
    }

    return 0;
}