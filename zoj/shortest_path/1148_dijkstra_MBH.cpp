#include "cstdio"
#include "cstring"
#include "functional"
#include "algorithm"
#include "vector"

template <int SZ, class T=int, class Op=std::less<T> >
class MBH {
    std::pair<int, T> heap[SZ+1];
    int key[SZ+1], sz;

public:
    void clear() {
        sz = 0; memset(key, 0, sizeof(key));
    }

    bool empty() const {
        return sz == 0;
    }

    std::pair<int, T> top() const {
        return heap[1];
    }

    void push(int idx, T val) {
        if (!key[idx]) {
            key[idx] = ++sz;
            heap[sz] = std::make_pair(idx, val);
        }
        else if (Op()(val, heap[key[idx]].second)) {
            heap[key[idx]].second = val;
        }

        for (int pos=key[idx], c; (c=pos>>1)&&Op()(val, heap[c].second);
            pos = c) {

            std::swap(heap[pos], heap[c]);
            key[idx] = c;
            key[heap[pos].first] = pos;
        } 
    }

    void pop() {
        key[heap[1].first] = 0;
        heap[1] = heap[sz--];
        if (sz == 0) return;

        key[heap[1].first] = 1;
        for (int pos=1, c; (c=pos<<1) <= sz; pos=c) {
            if (c<sz && Op()(heap[c+1].second, heap[c].second)) ++c;
            if (Op()(heap[c].second, heap[pos].second)) {
                std::swap(heap[c], heap[pos]);
                key[heap[c].first] = c;
                key[heap[pos].first] = pos;
            }
            else break;
        }
    }


};

struct Edge
{
    int end, len;
    Edge(int a=0, int b=0): end(a), len(b) {}
};

const int MAXN = 80;
const int inf = 0x12345678;
int w, h, N;
int x1, y1, x2, y2;
char board[MAXN][MAXN];
std::vector<Edge> edges[MAXN * MAXN];
int dis[MAXN * MAXN];
MBH<MAXN * MAXN> hp;

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
    dis[start] = 0;
    hp.clear();
    hp.push(start, 0);

    while (!hp.empty()) {
        int now = hp.top().first;
        hp.pop();

        for (int i=0; i<edges[now].size(); i++) {
            Edge &e = edges[now][i];
            if (dis[e.end] > dis[now] + e.len) {
                dis[e.end] = dis[now] + e.len;
                hp.push(e.end, dis[e.end]);
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