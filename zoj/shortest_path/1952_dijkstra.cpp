#include "cstdio"
#include "cstring"
#include "unordered_map"
#include "string"
#include "iostream"
#include "algorithm"

const int MAXN = 200;
int n, r;
short int value[MAXN][MAXN];
int dis[MAXN];
int visited[MAXN];
int start, end;

int min(int a, int b) {
    return a<b ? a:b;
}

void input()
{
    memset(value, 0, sizeof(value));
    std::unordered_map<std::string, int> m;
    std::string a, b;
    int aa, bb, c;
    int cur_num = 0;
    for (int i=0; i<r; i++) {
        std::cin >> a >> b >> c;
        if (m.count(a)) {
            aa = m[a];
        }
        else {
            aa = cur_num++;
            m[a] = aa;
        }
        if (m.count(b)) {
            bb = m[b];
        }
        else {
            bb = cur_num++;
            m[b] = bb;
        }
        value[aa][bb] = value[bb][aa] = c;
    }
    
    std::cin >> a >> b;
    start = m[a];
    end = m[b];
}

double dijkstra(int casen)
{
    memset(visited, 0, sizeof(visited));
    memset(dis, 0, sizeof(dis));

    int now = start;
    dis[now] = 10000;
    visited[now] = 1;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (!visited[j] && dis[j] < min(dis[now], value[now][j])) {
                dis[j] = min(dis[now], value[now][j]);
            }
        }

        int t = -1;
        for (int j=0; j<n; j++) {
            if (!visited[j] && dis[j] > t) {
                t = dis[j];
                now = j;
            }
        }
        visited[now] = 1;
    }
    std::cout << "Scenario #" << casen << std::endl;
    std::cout << dis[end] << " tons" << std::endl << std::endl;
}

int main(int argc, char const *argv[])
{
    int casen = 1;
    while (std::cin >> n >> r, n) {
        input();
        dijkstra(casen++);
    }
    return 0;
}
