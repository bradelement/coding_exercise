#include "cstdio"
#include "map"
using namespace std;

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

        map<int, int> mi;
        sum[0] = 0;
        mi[0] = 1;
        for (int i=1; i<=n; i++) {
            sum[i] = sum[i-1] + num[i];
            sum[i] %= m;
            mi[sum[i]]++;
        }

        int ans = 0;
        for (map<int, int>::iterator i=mi.begin(); i!=mi.end(); ++i) {
            if (i->second >= 2) {
                ans += i->second * (i->second-1) / 2;
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}