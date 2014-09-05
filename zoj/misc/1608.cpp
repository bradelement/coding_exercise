#include "cstdio"
#include "cmath"

double a, b, r1, r2;
bool gao() {
    return pow(a-r1-r2, 2) + pow(b-r1-r2, 2) >= pow(r1+r2, 2);
}

int main(int argc, char const *argv[])
{
    while (~scanf("%lf%lf%lf%lf", &a, &b, &r1, &r2)) {
        puts(gao() ? "Yes" : "No");
    }
    return 0;
}