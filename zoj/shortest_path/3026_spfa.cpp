#include "cstdio"
#include "cstring"
#include "vector"
#include "algorithm"
#include "queue"

struct Edge
{
    int end, len;
    Edge(int a=0, int b=0): end(a), len(b) {}
};

const int MAXN = 32;
const int inf = 0x12345678;
const int MAXNODE = MAXN * MAXN * 4;
std::vector<Edge> edges[MAXNODE];
bool inQue[MAXNODE];
int dis[MAXNODE];
int w, h, N;
int square[MAXN][MAXN];
int c[4];

const int UP    = 0;
const int RIGHT = 1;
const int DOWN  = 2;
const int LEFT  = 3;

inline int id(int i, int j, int k)
{
    return 4*(i*w+j)+k;
}

void _add(int i, int j, int k, int ii, int jj, int kk, int cmd)
{
    if (ii<0 || ii>=h || jj<0 || jj>=w) return;
    int cost = (square[i][j] == cmd ? 0 : c[cmd]);
    edges[id(i, j, k)].push_back(Edge(id(ii, jj, kk), cost));
}

void add_edge(int i, int j, int k)
{
    if (k == UP) {
        _add(i, j, UP, i-1, j, UP, 0);
        _add(i, j, UP, i, j+1, RIGHT, 1);
        _add(i, j, UP, i+1, j, DOWN, 2);
        _add(i, j, UP, i, j-1, LEFT, 3);
    } else if (k == RIGHT) {
        _add(i, j, RIGHT, i, j+1, RIGHT, 0);
        _add(i, j, RIGHT, i+1, j, DOWN, 1);
        _add(i, j, RIGHT, i, j-1, LEFT, 2);
        _add(i, j, RIGHT, i-1, j, UP, 3);
    } else if (k == DOWN) {
        _add(i, j, DOWN, i+1, j, DOWN, 0);
        _add(i, j, DOWN, i, j-1, LEFT, 1);
        _add(i, j, DOWN, i-1, j, UP, 2);
        _add(i, j, DOWN, i, j+1, RIGHT, 3);
    } else if (k == LEFT) {
        _add(i, j, LEFT, i, j-1, LEFT, 0);
        _add(i, j, LEFT, i-1, j, UP, 1);
        _add(i, j, LEFT, i, j+1, RIGHT, 2);
        _add(i, j, LEFT, i+1, j, DOWN, 3);
    }
}

void input()
{
    N = h*w*4;
    for (int i=0; i<N; i++) {
        edges[i].clear();
    }

    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            scanf("%d", &square[i][j]);
        }
    }
    scanf("%d%d%d%d", &c[0], &c[1], &c[2], &c[3]);
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            for (int k=0; k<4; k++) {//up, right, down, left
                add_edge(i, j, k);
            }
        }
    }
}

void spfa(int start)
{
    std::fill(dis, dis+N, inf);
    std::fill(inQue, inQue+N, false);
    std::queue<int> que;
    que.push(start);
    dis[start] = 0; inQue[start] = true;

    int cur, end, len;
    while (!que.empty()) {
        cur = que.front(); que.pop();
        inQue[cur] = false;

        for (int i=0; i<edges[cur].size(); i++) {
            end = edges[cur][i].end;
            len = edges[cur][i].len;
            if (dis[cur] + len < dis[end]) {
                dis[end] = dis[cur] + len;
                if (!inQue[end]) {
                    que.push(end);
                    inQue[end] = true;
                }
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    while (scanf("%d%d", &w, &h), w) {
        input();
        spfa(id(0, 0, RIGHT));
        int ans = inf, tmp;
        for (int i=0; i<4; i++) {
            tmp = dis[id(h-1, w-1, i)];
            if (tmp < ans) ans = tmp;
        }
        printf("%d\n", ans);
    }
    return 0;
}