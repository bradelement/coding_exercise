#include "cstdio"
#include "cmath"

const double inf = 0x12345678;

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
}

void gao(int a, int b)
{
    int g = gcd(a, b);
    a /= g; b /= g;

    double accurate = a * 1.0 / b;
    double cur_diff = inf;
    for (int i=1; i<=b; i++) {
        int n = accurate * i + 0.5;
        double diff = fabs(accurate - n * 1.0 / i);
        if (diff < cur_diff) {
            printf("%d/%d\n", n, i);
            cur_diff = diff;
        }
    }
}

int main(int argc, char const *argv[])
{
    int a, b;
    bool first = true;
    while (~scanf("%d%d", &a, &b)) {
        if (first) {
            first = false;
        }
        else {
            puts("");
        }
        gao(a, b);
    }
    return 0;
}