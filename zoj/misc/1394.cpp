#include "cstdio"
#include "cstring"

const double pi = 3.14159;
char line[16];
void gao()
{
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    if (z > 180) z = 360 - z;
    scanf("%s", line);

    double distance = 2*pi*x*(z / 360.0) * 2;//来回。。。
    int drive = y * 5;
    if (drive >= distance) {
        double re = (drive - distance) / 5;
        printf("YES %d\n", int(re));
    }
    else {
        printf("NO %d\n", drive);
    }
}

int main(int argc, char const *argv[])
{
    while (scanf("%s", line) && strcmp(line, "ENDOFINPUT")) {
        gao();
    }
    return 0;
}