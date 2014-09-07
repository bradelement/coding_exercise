#include "cstdio"
#include "cstring"
#include "vector"
#include "algorithm"
#include "queue"
using namespace std;

const int MAXN = 100001;
int N, M, K, L;
bool sensors[MAXN];
bool vis[MAXN];
bool reach[MAXN];
vector<int> edges[MAXN];
int t[MAXN];
queue<int> Que;

void input() {
    scanf("%d%d%d", &N, &M, &K);
    for (int i=1; i<=N; i++) {
        edges[i].clear();
    }
    fill(sensors, sensors+N+1, false);
    for (int i=0, x; i<K; i++) {
        scanf("%d", &x);
        sensors[x] = true;
    }
    for (int i=0, x, y; i<M; i++) {
        scanf("%d%d", &x, &y);
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    scanf("%d", &L);
    for (int i=0; i<L; i++) {
        scanf("%d", &t[i]);
    }
}

void bfs(int start) {
    while (!Que.empty()) Que.pop();

    Que.push(start);
    while (!Que.empty()) {
        int cur = Que.front(); Que.pop();
        if (vis[cur]) continue;
        reach[cur] = true;
        if (cur == start || !sensors[cur]) {
            vis[cur] = true;
            for (int i=0; i<edges[cur].size(); i++) {
                Que.push(edges[cur][i]);
            }
        }
    }
}

bool gao() {
    if (L != K) return false;

    fill(vis, vis+N+1, false);
    fill(reach, reach+N+1, false);//......
    for (int i=0; i<L; i++) {
        bfs(t[i]);
        if (i+1<L && !reach[t[i+1]]) return false;
    }
    for (int i=1; i<=N; i++) {
        if (!reach[i]) return false;
    }

    return true;
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--) {
        input();
        puts(gao() ? "Yes" : "No");
    }
    return 0;
}