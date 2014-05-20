#include "cstdio"
#include "iostream"
#include "queue"
#include "cstring"
using namespace std;

const int MAXN = 1024;
const int inf = 0x12345678;
int N, X, Y;
int xi, yi, xr, yr;
int map[MAXN][MAXN];
int used[MAXN][MAXN];
int ans[MAXN * 2];

typedef pair<int, int> Point;

void _debug() {
    printf("debug...\n");
    for (int i=0; i<X; i++) {
        for (int j=0; j<Y; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    printf("debug done...\n");
}

bool check(int x, int y, int r) {
    if (x<0 || y<0 || x>=X || y>=Y) return false;
    if (r >= map[x][y]) return false;
    map[x][y] = r;
    return true;
}

void make_shortest(queue<pair<Point, int> > &q) {
    int x, y, r;
    pair<Point, int> cur;

    while (!q.empty()) {
        cur = q.front(); q.pop();
        x = cur.first.first;
        y = cur.first.second;
        r = cur.second;
        
        if (check(x+1, y, r+1))q.push(make_pair(make_pair(x+1, y), r+1));
        if (check(x-1, y, r+1))q.push(make_pair(make_pair(x-1, y), r+1));
        if (check(x, y+1, r+1))q.push(make_pair(make_pair(x, y+1), r+1));
        if (check(x, y-1, r+1))q.push(make_pair(make_pair(x, y-1), r+1));
    }
}

void init() {
    scanf("%d%d%d", &N, &X, &Y);
    scanf("%d%d%d%d", &xi, &yi, &xr, &yr);
    for (int i=0; i<X; i++) {
        fill(map[i], map[i]+Y, inf);
    }
    queue<pair<Point, int> > q;
    int x, y;
    for (int i=0; i<N; i++) {
        scanf("%d%d", &x, &y);
        map[x][y] = 0;
        q.push(make_pair(make_pair(x, y), 0));
    }
    make_shortest(q);
}

bool check2(int x, int y, int lim) {
    if (x<0 || y<0 || x>=X || y>=Y || used[x][y]) return false;
    used[x][y] = 1;
    if (map[x][y] < lim) return false;
    return true;    
}

int bfs(int lim) {
    if (map[xi][yi] < lim) return -1;

    memset(used, 0, sizeof(used));
    pair<Point, int> cur = make_pair(make_pair(xi, yi), 0);
    queue<pair<Point, int> > q;
    q.push(cur);

    int x, y, r;
    while (!q.empty()) {
        cur = q.front(); q.pop();
        x = cur.first.first;
        y = cur.first.second;
        r = cur.second;
        if (x==xr && y==yr) return r;
        if (check2(x+1, y, lim))q.push(make_pair(make_pair(x+1, y), r+1));
        if (check2(x-1, y, lim))q.push(make_pair(make_pair(x-1, y), r+1));
        if (check2(x, y+1, lim))q.push(make_pair(make_pair(x, y+1), r+1));
        if (check2(x, y-1, lim))q.push(make_pair(make_pair(x, y-1), r+1));   
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    int casen;
    scanf("%d", &casen);
    while (casen--) {
        init();
        //_debug();
        int le=0, ri=X+Y-2;
        while (le<=ri) {
            int mid = (le+ri) / 2;
            ans[mid] = bfs(mid);
            if (ans[mid] >= 0) {
                le = mid + 1;
            }
            else {
                ri = mid - 1;
            }
        }
        printf("%d %d\n", ri, ans[ri]);
    }

    return 0;
}