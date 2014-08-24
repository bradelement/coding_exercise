#include "cstdio"

const int MAXN = 10240;
int n, m;
int num[MAXN];
int sum[MAXN];

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d", &n, &m)) {
        for (int i=1; i<=n; i++) {
            scanf("%d", &num[i]);
            num[i] %= m;
        }
        sum[0] = 0;
        for (int i=1; i<=n; i++) {
            sum[i] = sum[i-1] + num[i];
        }

        int ans = 0;
        for (int i=1; i<=n; i++) {
            for (int j=i; j<=n; j++) {
                if ((sum[j] - sum[i-1]) % m == 0) {
                    ans++;
                }
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}