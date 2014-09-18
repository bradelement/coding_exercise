#include "cstdio"
const double inf = 0x12345678;
const double eps = 1e-8;

int T, N;
double A, next;

double check(double next) {
    double a = A, b = next;
    for (int i=0; i<N-2; i++) {
        next = (b+1) * 2 - a;
        if (next < 0) return -1;
        a = b;
        b = next;
    }
    return next;
}

int main(int argc, char const *argv[])
{
    scanf("%d", &T);
    while (T--) {
        scanf("%d%lf", &N, &A);

        double low = 0, high = inf;
        double ans = 0;
        while (low + eps < high) {
            double mid = (low + high) / 2;
            double tmp = check(mid);
            if (tmp >= 0) {
                ans = tmp;
                high = mid;
            }
            else {
                low = mid;
            }
        }
        printf("%.2lf\n", ans);
        if (T) printf("\n");
    }
    return 0;
}