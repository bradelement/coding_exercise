#include "cstdio"

void factor(long long n) {
    while (n>=4 && (n%2 == 0)) {
        printf("2\n");
        n /= 2;
    }
    long long m = 3;
    while (m * m <= n) {
        if (n % m == 0) {
            printf("%lld\n", m);
            n /= m;
        }
        else {
            m += 2;
        }
    }
    printf("%lld\n\n", n);
}
//标准做法 快速素数测试？学习Miller_Rabin..
int main(int argc, char const *argv[])
{
    long long n;
    while (scanf("%lld", &n), n >= 0) {
        factor(n);
    }
    return 0;
}