#include "cstdio"
#include "cstring"
#include "vector"
using namespace std;

struct Point {
    int x, y;
    Point(int a=0, int b=0): x(a), y(b) {}
};

int n, r, c;
char grid[10][80];

bool gao1(const vector<vector<Point> > &vv, int idx) {
    const vector<Point> &vp = vv[idx];
    for (int i=0; i<vp.size(); i++) {
        bool flag = true;
        for (int j=0; j<n; j++) {
            if (j == idx) continue;
            int x = vp[i].x;
            int y = vp[i].y - idx * (c+1);

            if (grid[x][y+j*(c+1)] != '.') {
                flag = false;
                break;
            }
        }
        if (flag) {
            grid[vp[i].x][vp[i].y] = '#';
            return true;
        }
    }
    return false;
}

bool gao2(const vector<vector<Point> > &vv, int idx) {
    const vector<Point> &vp = vv[idx];
    for (int i=0; i<vp.size(); i++) {
        for (int j=i+1; j<vp.size(); j++) {
            int x1 = vp[i].x;
            int y1 = vp[i].y - idx * (c+1);
            int x2 = vp[j].x;
            int y2 = vp[j].y - idx * (c+1);

            bool flag = true;
            for (int k=0; k<n; k++) {
                if (k == idx) continue;

                if (grid[x1][y1+k*(c+1)] != '.' && grid[x2][y2+k*(c+1)] != '.') {
                    flag = false;
                    break;
                } 
            }
            if (flag) {
                grid[x1][vp[i].y] = grid[x2][vp[j].y] = '#';
                return true;
            }
        }
    }
    return false;
}

bool gao() {
    vector<vector<Point> > vv;
    for (int k=0; k<n; k++) {
        vector<Point> vp;
        int x = 0, y = k*(c+1);
        for (int i=0; i<r; i++) {
            for (int j=y; j<y+c; j++) {
                if (grid[i][j] == 'o') {
                    vp.push_back(Point(i, j));
                }
            }
        }
        vv.push_back(vp);
    }

    for (int k=0; k<n; k++) {
        if (!gao1(vv, k)) {
            if (!gao2(vv, k)) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char const *argv[])
{
    int ci = 1;
    while (scanf("%d%d%d", &n, &r, &c), n) {
        gets(grid[0]);
        for (int i=0; i<r; i++) {
            gets(grid[i]);
        }

        bool ret = gao();
        printf("Test %d\n", ci++);
        if (ret) {
            for (int i=0; i<r; i++) {
                puts(grid[i]);
            }
        }
        else {
            puts("impossible");
        }
    }
    return 0;
}