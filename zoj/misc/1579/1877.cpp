#include "cstdio"
#include "algorithm"
using namespace std;

const int MAXN = 1001;
int a[MAXN];
int dp[MAXN];
bool mins[MAXN];

/*
    递推： dp[i]为把前i-2人送过去 最小的两人再回来。
           或前i-1送过去 最小的回来接。
*/

int main(int argc, char const *argv[])
{
    int n, i;
    while (~scanf("%d", &n)) {
        for (i=0; i<n; i++) {
            scanf("%d", &a[i]);
        }
        sort(a, a+n);
        
        dp[0] = 0;
        dp[1] = a[0];
        dp[2] = a[1];
        dp[3] = a[0] + a[1] + a[2];

        for (i=4; i<=n; i++) {
            dp[i] = dp[i-2] + a[1] + a[i-1] + a[0] + a[1];
            mins[i] = false;
            int tmp = dp[i-1]+a[0]+a[i-1];
            if (tmp < dp[i]) {
                dp[i] = tmp;
                mins[i] = true;
            }
        }
        printf("%d\n", dp[n]);
        for (i=n; i>3; ) {
            if (mins[i]) {
                printf("%d %d\n", a[i-1], a[0]);
                printf("%d\n", a[0]);       
                i--;              
            }
            else {
                printf("%d %d\n", a[0], a[1]);
                printf("%d\n", a[0]);
                printf("%d %d\n", a[i-1], a[i-2]);
                printf("%d\n", a[1]);
                i -= 2;
            }
        }
        if (i == 3) {
            printf("%d %d\n", a[0], a[1]);
            printf("%d\n", a[0]);
            printf("%d %d\n", a[0], a[2]);
        }
        else if (i == 2) {
            printf("%d %d\n", a[0], a[1]);
        }
        else {
            printf("%d\n", a[0]);
        }
    }

    return 0;
}