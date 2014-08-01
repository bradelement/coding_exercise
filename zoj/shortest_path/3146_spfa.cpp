#include "cstdio"
#include "set"
#include "algorithm"
#include "climits"
#include "queue"

const int MAXN = 30;
struct Edge
{
    int end, len;
    Edge(int a=0, int b=0): end(a), len(b) {}
    bool operator< (const Edge &e) const {
        return end < e.end || (end == e.end && len < e.len);
    }
};

int n, m, r, c;
int forest[MAXN][MAXN];
std::set<Edge> edges[MAXN * MAXN];
int start, finish;
bool inQue[MAXN * MAXN];
int dis[MAXN * MAXN];

int cal_id(int i, int j)
{
    if (i<0) i=0;
    else if (i>=n) i=n-1;
    if (j<0) j=0;
    else if (j>=m) j=m-1;
    return i*m + j;
}

void input()
{
    start = cal_id(r-1, c-1);
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            scanf("%d", &forest[i][j]);
            if (forest[i][j] == 0) {
                finish = cal_id(i, j);
            }
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            int cur = cal_id(i, j);
            edges[cur].clear();
            edges[cur].insert(Edge(cal_id(i+forest[i][j], j), forest[i][j]));
            edges[cur].insert(Edge(cal_id(i-forest[i][j], j), forest[i][j]));
            edges[cur].insert(Edge(cal_id(i, j+forest[i][j]), forest[i][j]));
            edges[cur].insert(Edge(cal_id(i, j-forest[i][j]), forest[i][j]));
        }
    }
}

void spfa()
{
    std::fill(dis, dis+n*m, INT_MAX);
    std::fill(inQue, inQue+n*m, false);

    std::queue<int> que;
    que.push(start);
    dis[start] = 0; inQue[start] = true;

    int cur, end, len;
    while (!que.empty()) {
        cur = que.front(); que.pop();
        inQue[cur] = false;

        for (std::set<Edge>::iterator i=edges[cur].begin(); \
            i!=edges[cur].end(); ++i) {
            end = i->end;
            len = i->len;
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

void output()
{
    if (dis[finish] == INT_MAX) {
        printf("No solution\n");
    }
    else {
        printf("%d\n", dis[finish]);
    }
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d%d%d", &n, &m, &r, &c)) {
        input();
        spfa();
        output();
    }
    return 0;
}