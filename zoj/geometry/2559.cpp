#include "cstdio"
#include "cmath"

struct Point {
    int x, y;
};
Point points[3];

double distance(Point &a, Point &b) {
    return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d", &points[0].x, &points[0].y)) {
        for (int i=1; i<3; i++) {
            scanf("%d%d", &points[i].x, &points[i].y);
        }
        double ab, ac, bc;
        ab = distance(points[0], points[1]);
        ac = distance(points[0], points[2]);
        bc = distance(points[1], points[2]);
        double sum = (ab + ac + bc) / 2;

        printf("%lf\n", sum - bc);
        printf("%lf\n", sum - ac);
        printf("%lf\n", sum - ab);
    }
    return 0;
}