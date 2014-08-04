#include "cstdio"
#include "queue"
#include "vector"
#include "string"
#include "map"
#include "set"
#include "algorithm"
#include "iostream"
#include "climits"

struct Edge
{
    int end, len;
    Edge(int a=0, int b=0): end(a), len(b) {}
};

const int MAXN = 1024;
const int inf = 0x12345678;
int N;
std::vector<Edge> edges[MAXN];
bool inQue[MAXN];
int dis[MAXN];

void init()
{
    std::map<std::string, std::set<int> > m;
    std::vector<std::string> word(N);
    std::vector<int> len(N);
    for (int i=0; i<N; i++) {
        std::cin >> len[i] >> word[i];
        m[word[i].substr(0, 4)].insert(i);
        edges[i].clear();
    }
    for (int i=0; i<N; i++) {
        std::set<int> &v = m[word[i].substr(word[i].length()-4)];
        for (std::set<int>::iterator j=v.begin(); j!=v.end(); ++j) {
            if (*j != i) {
                edges[i].push_back(Edge(*j, len[i]));
            }
        }
    }
}

void spfa()
{
    std::fill(dis, dis+N, inf);
    std::fill(inQue, inQue+N, false);
    std::queue<int> que;
    int start = 0;
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
    while (std::cin >> N, N) {
        init();
        spfa();
        if (dis[N-1] < inf) {
            std::cout << dis[N-1] << std::endl;    
        } else {
            std::cout << -1 << std::endl;
        }
    }
    return 0;
}

