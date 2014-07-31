#include <cstdio>
#include <cmath>

const double pi = asin(1.0) * 2;

int main(int argc, char const *argv[])
{
    int a, b, s, m, n;
    while (scanf("%d%d%d%d%d", &a, &b, &s, &m, &n), s) {
        double v_h = (a * m * 1.0) / s;
        double v_v = (b * n * 1.0) / s;
        double v = sqrt(v_h * v_h + v_v * v_v);
        double angle = atan(v_v / v_h) * 180 / pi;
        printf("%.2lf %.2lf\n", angle, v);
    }

    return 0;
}