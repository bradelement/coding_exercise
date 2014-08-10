#include "cstdio"
#include "cstring"
#include "functional"
#include "algorithm"
#include "vector"
#include "queue"

struct Edge
{
    int end, len;
    Edge(int a=0, int b=0): end(a), len(b) {}

    bool operator< (const Edge &e) const {
        return len > e.len;
    }
};

const int MAXN = 80;
const int inf = 0x12345678;
int w, h, N;
int x1, y1, x2, y2;
char board[MAXN][MAXN];
std::vector<Edge> edges[MAXN * MAXN];
int dis[MAXN * MAXN];
typedef std::pair<int, int> Pii;
std::priority_queue<Pii> que;

int id(int i, int j)
{
    return i*(w+2) +j;
}

void add_edge(int i, int j)
{
    int curid = id(i, j);
    int curi, curj;
    curi = i+1;
    while (curi <= h+1) {
        if (board[curi][j] == 'X') break;
        edges[curid].push_back(Edge(id(curi, j), 1));
        curi++;
    }
    curi = i-1;
    while (curi >= 0) {
        if (board[curi][j] == 'X') break;
        edges[curid].push_back(Edge(id(curi, j), 1));
        curi--;
    }
    curj = j+1;
    while (curj <= w+1) {
        if (board[i][curj] == 'X') break;
        edges[curid].push_back(Edge(id(i, curj), 1));
        curj++;
    }
    curj = j-1;
    while (curj >= 0) {
        if (board[i][curj] == 'X') break;
        edges[curid].push_back(Edge(id(i, curj), 1));
        curj--;
    }
}

void input()
{
    for (int i=0; i<=h+1; i++) {
        for (int j=0; j<=w+1; j++) {
            board[i][j] = ' ';
        }
    }
    gets(board[1]+1);
    for (int i=1; i<=h; i++) {
        gets(board[i]+1);
    }

    N = (h+2)*(w+2);
}

void dijkstra(int start)
{
    std::fill(dis, dis+N, inf);
    while (!que.empty()) que.pop();
    dis[start] = 0;
    que.push(std::make_pair(start, 0));

    Pii ce;
    while (!que.empty()) {
        ce = que.top(); que.pop();
        int now = ce.first;
        if (dis[now] != ce.second) continue;
        
        for (int i=0; i<edges[now].size(); i++) {
            Edge &e = edges[now][i];
            if (dis[e.end] > dis[now] + e.len) {
                dis[e.end] = dis[now] + e.len;
                que.push(std::make_pair(e.end, dis[e.end]));
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    int bn = 1;
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    while (scanf("%d%d", &w, &h), w) {
        input();
        printf("Board #%d:\n", bn++);
        int pn = 1;
        while (scanf("%d%d%d%d", &y1, &x1, &y2, &x2), x1) {
            board[x2][y2] = ' ';
            for (int i=0; i<=h+1; i++) {
                for (int j=0; j<=w+1; j++) {
                    edges[id(i, j)].clear();
                    add_edge(i, j);
                }
            }
            dijkstra(id(x1, y1));
            board[x2][y2] = 'X';
            printf("Pair %d: ", pn++);
            int ans = dis[id(x2, y2)];
            if (ans == inf) {
                puts("impossible.");
            }
            else {
                printf("%d segments.\n", ans);
            }
        }
        printf("\n");
    }
    return 0;
}