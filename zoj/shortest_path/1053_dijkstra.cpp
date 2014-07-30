#include "cstdio"
#include "cstring"
#include "string"
#include "iostream"
#include "sstream"
#include "algorithm"
#include "vector"
#include "map"

const int MAXN = 22;
const int inf = 0x3f3f3f3f;
int n;
int value[MAXN][MAXN];
int dis[MAXN];
int visited[MAXN];
int prev[MAXN];

int start, end;
std::vector<int> destination;

void input()
{
    std::cin >> n;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            std::cin >> value[i][j];
        }
    }
    std::string line;
    getline(std::cin, line);
    getline(std::cin, line);
    std::stringstream si(line);
    si >> start;
    destination.clear();
    while (si >> end) {
        destination.push_back(end);
    }
}

void dijkstra()
{
    memset(visited, 0, sizeof(visited));
    std::fill(dis, dis+n+1, inf);

    int now = start;
    dis[now] = 0;
    visited[now] = 1;
    for (int i=1; i<n; i++) {
        for (int j=1; j<=n; j++) {
            if (!visited[j] && value[j][now] >= 0 && dis[j] > dis[now] + value[j][now]) {
                dis[j] = dis[now] + value[j][now];
                prev[j] = now;
            }
        }

        int t = inf;
        for (int j=1; j<=n; j++) {
            if (!visited[j] && dis[j] < t) {
                t = dis[j];
                now = j;
            }
        }
        visited[now] = 1;
    }
}

void output()
{
    std::cout << "Org\tDest\tTime\tPath" << std::endl;
    std::map<int, int> m;
    for (int i=0; i<destination.size(); i++) {
        m[dis[destination[i]]] = destination[i];
    }
    
    for (auto i=m.begin(); i!=m.end(); ++i) {
        int cur = i->second;
        std::cout << cur << '\t' << start << '\t' << i->first;
        std::cout << '\t' << cur;
        while (cur != start) {
            cur = prev[cur];
            std::cout << '\t' << cur;
        };
        std::cout << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    int casen;
    std::cin >> casen;
    for (int i=0; i<casen; i++) {
        if (i) std::cout << std::endl;
        input();
        dijkstra();
        output();
    }
    
    return 0;
}
