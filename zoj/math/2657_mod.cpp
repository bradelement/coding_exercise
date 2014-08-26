#include "cstdio"

int X, Y, M, N, L;

typedef long long LL;

LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    LL r = exgcd(b, a%b, x, y);
    LL t = x;
    x = y;
    y = t - a/b*y;
    return r;
}

//返回最小解 -1表示无解
// a*x === b (mod n)
LL modular_linear_equation(LL a, LL b, LL n)
{
    LL d, x, y;
    d = exgcd(a, n, x, y);
    if (b % d) return -1;

    LL x0 = x * (b / d);
    x0 = (x0 % n + n) % n;

    return x0 % (n / d);
}

// X+M*t === Y+N*t (mod L)
int main(int argc, char const *argv[])
{
    while (~scanf("%d%d%d%d%d", &X, &Y, &M, &N, &L)) {
        int ans = modular_linear_equation(N-M, X-Y, L);
        if (ans == -1) {
            puts("Pat");
        }
        else {
            printf("%d\n", ans);
        }
    }
    return 0;
}