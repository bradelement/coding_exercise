#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

const int MAXN = 100001;
int a[MAXN];
long long sum[MAXN];

int l[MAXN], r[MAXN];

int main(int argc, char const *argv[])
{
    int n;
    while (~scanf("%d", &n)) {
        sum[0] = 0;
        for (int i=1; i<=n; i++) {
            scanf("%d", &a[i]);
            sum[i] = sum[i-1] + a[i];
        }

        for (int i=1; i<=n; i++) {
            l[i] = i;
            while (l[i]>1 && a[i] <= a[l[i]-1]) {
                l[i] = l[l[i]-1];
            }
        }
        for (int i=n; i>=1; i--) {
            r[i] = i;
            while (r[i]<n && a[i] <= a[r[i]+1]) {
                r[i] = r[r[i]+1];
            }
        }

        long long ret = 0, tmp;
        int left, right;
        for (int i=1; i<=n; i++) {
            tmp = (sum[r[i]]-sum[l[i]-1]) * a[i];
            if (tmp > ret) {
                ret = tmp;
                left = l[i];
                right = r[i];
            }
        }
        printf("%lld\n", ret);
        printf("%d %d\n", left, right);
    }

    
    return 0;
}