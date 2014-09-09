#include "cstdio"
#include "cstring"
#include "list"

struct Point
{
    int x, y;
    Point(int a=0, int b=0): x(a), y(b) {}
    bool operator== (const Point &other) const {
        return x == other.x && y == other.y;
    }
};
int n;
char line[128];

Point move(Point p, char dir) {
    Point ret = p;
    if (dir == 'N') {
        ret.x--;
    }
    else if (dir == 'S') {
        ret.x++;
    }
    else if (dir == 'W') {
        ret.y--;
    }
    else if (dir == 'E') {
        ret.y++;
    }
    return ret;
}

bool valid(Point p) {
    return p.x >= 1 && p.x <= 50 && p.y >= 1 && p.y <= 50;
}

void gao() {
    std::list<Point> worm;
    for (int i=11; i<=30; i++) {
        worm.push_front(Point(25, i));
    }
    for (int i=1; i<=n; i++) {
        worm.pop_back();
        Point new_head = move(worm.front(), line[i-1]);
        if (!valid(new_head)) {
            printf("The worm ran off the board on move %d.\n", i);
            return;
        }
        for (std::list<Point>::iterator it=worm.begin(); it!=worm.end(); ++it) {
            if ((*it) == new_head) {
                printf("The worm ran into itself on move %d.\n", i);
                return;
            }
        }
        worm.push_front(new_head);
    }
    printf("The worm successfully made all %d moves.\n", n);
}

int main(int argc, char const *argv[])
{
    while (scanf("%d", &n), n) {
        gets(line);
        gets(line);
        gao();
    }
    return 0;
}