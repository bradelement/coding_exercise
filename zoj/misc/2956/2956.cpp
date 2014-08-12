#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
#include "algorithm"
using namespace std;

const int MAXN = 4096;
pair<int, int> a[MAXN*2];
int n;

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i=0; i<n; i++) {
            scanf("%*d%d%d", &a[2*i].first, &a[2*i+1].first);
            a[2*i+1].first++;
            a[2*i].second = 1;
            a[2*i+1].second = -1;
        }
        sort(a, a+2*n);

        int ret = 0;
        int maxret = 0;
        for (int i=0; i<2*n; i++) {
            ret += a[i].second;
            if (ret > maxret) maxret = ret;
        }
        printf("%d\n", maxret);
    }

    return 0;
}