#include "iostream"
#include "stack"
#include "cstdio"
using namespace std;

const int MAXN = 100000;
int a[MAXN], l[MAXN], r[MAXN];

int main(int argc, char const *argv[])
{
    int n;
    while (scanf("%d", &n), n) {
        for (int i=0; i<n; i++) {
            scanf("%d", &a[i]);
        }

        for (int i=0; i<n; i++) {
            l[i] = i;
            while (l[i] && a[i] <= a[l[i]-1]) {
                l[i] = l[l[i]-1];
            }
        }
        for (int i=n-1; i>=0; i--) {
            r[i] = i;
            while (r[i]<n-1 && a[i] <= a[r[i]+1]) {
                r[i] = r[r[i]+1];
            }
        }
        long long ret = 0;
        long long tmp;
        for (int i=0; i<n; i++) {
            tmp = (long long)a[i] * (r[i]-l[i]+1);
            if (tmp > ret) ret = tmp;
        }
        printf("%lld\n", ret);
    }

    return 0;
}