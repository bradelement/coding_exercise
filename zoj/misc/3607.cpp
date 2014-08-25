#include "cstdio"

const int MAXN = 1024;
const int inf = 0x12345678;
int p[MAXN], t[MAXN];
int n;

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i=1; i<=n; i++) {
            scanf("%d", &p[i]);
        }
        for (int i=1; i<=n; i++) {
            scanf("%d", &t[i]);
        }
        p[0] = t[0] = 0;
        t[n+1] = inf;

        int sum = 0, mlen = -1;
        double max_ave = -1, max_len;
        for (int i=1; i<=n; i++) {
            sum += p[i];
            double ave = sum * 1.0 / i;
            int cur_len = t[i] - t[i-1];
            if (cur_len > mlen) mlen = cur_len;
            if (ave > max_ave && t[i+1] - t[i] > mlen) {//第二个条件果然是亮点。。。。
                max_ave = ave;
                max_len = mlen;
            }
        }
        printf("%.6lf %.6lf\n", max_len, max_ave);
    }
    return 0;
}
