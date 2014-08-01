#include "cstdio"
#include "vector"
#include "iostream"
#include "queue"

struct Edge
{
    int end, len;
    Edge(int a=0, int b=0): end(a), len(b) {}
};

const int MAXN = 1001;
const int inf = 0x3f3f3f3f;
int n, m, k;
std::vector<Edge> slopes[MAXN], lifts[MAXN];
int dis[MAXN][MAXN], dis2[MAXN][MAXN];
int prev[MAXN][MAXN], prev2[MAXN][MAXN];
bool inQue[MAXN];

void input()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i=1; i<=n; i++) {
        slopes[i].clear();
        lifts[i].clear();
    }
    int a, b, c;
    for (int i=0; i<m; i++) {
        scanf("%d%d%d", &a, &b, &c);
        slopes[a].push_back(Edge(b, c));
    }
    for (int i=0; i<k; i++) {
        scanf("%d%d%d", &a, &b, &c);
        lifts[a].push_back(Edge(b, c));
    }
}

void spfa(int start)
{
    std::fill(inQue+1, inQue+n+1, false);
    std::fill(dis[start]+1, dis[start]+n+1, 0);
    std::queue<int> que;
    que.push(start);
    dis[start][start] = 0; inQue[start] = true;

    int cur, end, len;
    while (!que.empty()) {
        cur = que.front(); que.pop();
        inQue[cur] = false;

        for (int i=0; i<slopes[cur].size(); i++) {
            end = slopes[cur][i].end;
            len = slopes[cur][i].len;
            if (dis[start][cur] + len > dis[start][end]) {
                dis[start][end] = dis[start][cur] + len;
                prev[start][end] = cur;
                if (!inQue[end]) {
                    que.push(end);
                    inQue[end] = true;
                }
            }
        }
    }
}

void spfa2(int start)
{
    std::fill(inQue+1, inQue+n+1, false);
    std::fill(dis2[start]+1, dis2[start]+n+1, inf);
    std::queue<int> que;
    que.push(start);
    dis2[start][start] = 0; inQue[start] = true;

    int cur, end, len;
    while (!que.empty()) {
        cur = que.front(); que.pop();
        inQue[cur] = false;

        for (int i=0; i<lifts[cur].size(); i++) {
            end = lifts[cur][i].end;
            len = lifts[cur][i].len;
            if (dis2[start][cur] + len < dis2[start][end]) {
                dis2[start][end] = dis2[start][cur] + len;
                prev2[start][end] = cur;
                if (!inQue[end]) {
                    que.push(end);
                    inQue[end] = true;
                }
            }
        }
    }
}

void print(int begin, int end)
{
    if (begin == end) return;
    print(begin, prev[begin][end]);
    printf(" %d", end);
}

void print2(int begin, int end)
{
    if (begin == end) return;
    print2(begin, prev2[begin][end]);
    printf(" %d", end);
}

int main(int argc, char const *argv[])
{
    int casen;
    scanf("%d", &casen);
    while (casen--) {
        input();
        for (int i=1; i<=n; i++) {
            spfa(i);
            spfa2(i);
        }
        double mx = -1, rate;
        int begin, end;
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {                
                if (i == j || dis[i][j] == 0 || dis2[j][i] == inf) continue;
                rate = dis[i][j] * 1.0 / dis2[j][i];
                if (rate > mx) {
                    mx = rate;
                    begin = i; end = j;
                }
            }
        }
        printf("%d", end);
        print2(end, begin);
        print(begin, end);
        printf("\n%.3lf\n", mx);
    }

    return 0;
}