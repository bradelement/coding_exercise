#include "cstdio"
#include "algorithm"
using namespace std;

const int MAXN = 100001;
long long a[MAXN];
long long dp[MAXN];

/*
    递推： dp[i]为把前i-2人送过去 最小的两人再回来。
           或前i-1送过去 最小的回来接。
*/

int main(int argc, char const *argv[])
{
    int n;
    while (~scanf("%d", &n)) {
        for (int i=0; i<n; i++) {
            scanf("%lld", &a[i]);
        }
        sort(a, a+n);
        dp[0] = 0;
        dp[1] = a[0];
        dp[2] = a[1];

        for (int i=3; i<=n; i++) {
            dp[i] = dp[i-2] + a[1] + a[i-1] + a[0] + a[1];
            dp[i] = min(dp[i], dp[i-1]+a[0]+a[i-1]);
        }
        printf("%lld\n", dp[n]);
    }

    return 0;
}