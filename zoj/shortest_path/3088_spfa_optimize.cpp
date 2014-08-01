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
int dis[MAXN], dis2[MAXN];
int prev[MAXN], prev2[MAXN];
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
        slopes[b].push_back(Edge(a, c));
    }
    for (int i=0; i<k; i++) {
        scanf("%d%d%d", &a, &b, &c);
        lifts[a].push_back(Edge(b, c));
    }
}

void spfa(int start)
{
    std::fill(inQue+1, inQue+n+1, false);
    std::fill(dis+1, dis+n+1, 0);
    std::queue<int> que;
    que.push(start);
    dis[start] = 0; inQue[start] = true;

    int cur, end, len;
    while (!que.empty()) {
        cur = que.front(); que.pop();
        inQue[cur] = false;

        for (int i=0; i<slopes[cur].size(); i++) {
            end = slopes[cur][i].end;
            len = slopes[cur][i].len;
            if (dis[cur] + len > dis[end]) {
                dis[end] = dis[cur] + len;
                prev[end] = cur;
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
    std::fill(dis2+1, dis2+n+1, inf);
    std::queue<int> que;
    que.push(start);
    dis2[start] = 0; inQue[start] = true;

    int cur, end, len;
    while (!que.empty()) {
        cur = que.front(); que.pop();
        inQue[cur] = false;

        for (int i=0; i<lifts[cur].size(); i++) {
            end = lifts[cur][i].end;
            len = lifts[cur][i].len;
            if (dis2[cur] + len < dis2[end]) {
                dis2[end] = dis2[cur] + len;
                prev2[end] = cur;
                if (!inQue[end]) {
                    que.push(end);
                    inQue[end] = true;
                }
            }
        }
    }
}

void store_path(int begin, int end, std::vector<int> &path)
{
    path.push_back(end);
    if (begin == end) return;
    store_path(begin, prev[end], path);
}

void store_path2(int begin, int end, std::vector<int> &path)
{
    if (begin == end) return;
    store_path2(begin, prev2[end], path);
    path.push_back(end);
}

int main(int argc, char const *argv[])
{
    int casen;
    scanf("%d", &casen);
    while (casen--) {
        input();
        double mx = 0, rate;
        int begin, end;
        std::vector<int> path;
        for (int i=1; i<=n; i++) {
            spfa(i);
            spfa2(i);
            for (int j=1; j<=n; j++) {
                if (i == j || dis[j] == 0 || dis2[j] == inf) continue;
                rate = dis[j] * 1.0 / dis2[j];
                if (rate > mx) {
                    mx = rate;
                    begin = i; end = j;
                    path.clear();    
                    path.push_back(begin);
                    store_path2(begin, end, path);
                    std::vector<int> path2;
                    store_path(begin, end, path2);
                    for (int i=1; i<path2.size(); i++) {
                        path.push_back(path2[i]);
                    }
                }
            }
        }
        for (int i=0; i<path.size(); i++) {
            if (i) printf(" ");
            printf("%d", path[i]);
        }
        printf("\n%.3lf\n", mx);
    }

    return 0;
}