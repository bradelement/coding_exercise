#include "cstdio"

double rate[5][5];
int country[10];

double format(double money) {
    int m = money*100 + 0.5;
    return m / 100.0;
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--) {
        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                scanf("%lf", &rate[i][j]);
            }
        }
        int n;
        double money;
        while (scanf("%d", &n), n) {
            for (int i=0; i<n; i++) {
                scanf("%d", &country[i]);
                country[i] -= 1;
            }
            scanf("%lf", &money);
            int prev = 0;
            for (int i=0; i<n; i++) {
                money *= rate[prev][country[i]];
                money = format(money);
                prev = country[i];
            }
            money *= rate[country[n-1]][0];
            printf("%.2lf\n", money);
        }
        if (T) {
            puts("");
        }
    }
    return 0;
}