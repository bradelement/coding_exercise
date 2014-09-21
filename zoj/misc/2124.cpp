#include "cstdio"
#include "cmath"

int mypow(int a, int b) {
    int ret = 1;
    while (b--) {
        ret *= a;
    }
    return ret;
}

int gao_negative(long long n) {
    int lim = log(-n) / log(2) + 1;
    lim |= 1;
    for (int b=lim; b>=3; b-=2) {
        int base = -pow(-n, 1.0/b);
        for (int i=-1; i<=1; i++) {
            if (mypow(base+i, b) == n) {
                return b;
            }
        }
    }
    return 1;
}

int gao_positive(int n) {
    int lim = log(n) / log(2) + 1;
    for (int b=lim; b>=2; b--) {
        int base = pow(n, 1.0/b);
        for (int i=-1; i<=1; i++) {
            if (mypow(base+i, b) == n) {
                return b;
            }
        }
    }
    return 1;
}

int gao(int n) {
    return n > 0 ? gao_positive(n) : gao_negative(n);
}

int main(int argc, char const *argv[])
{
    int n;
    while (scanf("%d", &n), n) {
        printf("%d\n", gao(n));
    }
    return 0;
}