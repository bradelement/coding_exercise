#include "cstdio"

struct Circle {
    int x, y, r;
};

const int MAXN = 10000;
const int seg = 500;
Circle c[MAXN];
double x1, y1, x2, y2;
int N;

double sq(double x) 
{
    return x * x;
}

bool in_circle(double x, double y) {
    for (int i=0; i<N; i++) {
        if (sq(x-c[i].x) + sq(y-c[i].y) <= sq(c[i].r)) return true;
    }
    return false;
}

int main(int argc, char const *argv[])
{
    while (scanf("%d", &N), N) {
        for (int i=0; i<N; i++) {
            scanf("%d%d%d", &c[i].x, &c[i].y, &c[i].r);
        }
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        double mx = (x1+x2) / 2.0;
        double my = (y1+y2) / 2.0;

        double sx = (mx-x1) / seg;
        double sy = (my-y1) / seg;
        bool left = false, right = false;
        for (int i=0; i<seg; i++) {
            if (in_circle(x1, y1)) {
                left = true;
                break;
            }
            x1 += sx; y1 += sy;
        }
        if (!left) goto out;
        sx = (mx-x2) / seg;
        sy = (my-y2) / seg;
        for (int i=0; i<seg; i++) {
            if (in_circle(x2, y2)) {
                right = true;
                break;
            }
            x2 += sx; y2 += sy;
        }
out:
        if (left && right) {
            puts("STAY");
        }
        else {
            puts("FALL");
        }

    }
    return 0;
}