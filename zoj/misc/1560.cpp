#include "cstdio"
#include "cmath"

const double pi = acos(-1);

int change(int angle)
{
    return (450 - angle) % 360;
}

int main(int argc, char const *argv[])
{
    int n;
    int x1, y1, d1, x2, y2, d2;
    scanf("%d", &n);
    double x, y;
    double k1, k2, b1, b2;
    while (n--) {
        scanf("%d%d%d%d%d%d", &x1, &y1, &d1, &x2, &y2, &d2);
        d1 = change(d1);
        d2 = change(d2);
        if (d1 == 90 || d1 == 270) {
            x = x1;
        }
        else {
            k1 = tan(d1 * pi / 180);
            b1 = -1 * k1 * x1 + y1;
        }

        if (d2 == 90 || d2 == 270) {
            x = x2;
            y = k1 * x + b1;
        }
        else {
            k2 = tan(d2 * pi / 180);
            b2 = -1 * k2 * x2 + y2;
            if (d1 == 90 || d1 == 270) {
                y = k2 * x + b2;
            }
            else {
                x = (b2 - b1) / (k1 - k2);
                y = k1 * x + b1;
            }
        }
        printf("%.4lf %.4lf\n", x, y);
    }
    return 0;
}