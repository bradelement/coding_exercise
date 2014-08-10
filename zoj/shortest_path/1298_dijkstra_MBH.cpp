#include "cstdio"
#include "cstring"
#include "cstdlib"
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

const int MAXN = 512;
const int inf = 0x12345678;
const double eps = 1e-6;
int n, m;
std::vector<Edge> edges[MAXN];
int dis[MAXN];
MBH<MAXN> hp;

void input()
{
    for (int i=1; i<=n; i++) {
        edges[i].clear();
    }

    int a, b, l;
    for (int i=0; i<m; i++) {
        scanf("%d%d%d", &a, &b, &l);
        edges[a].push_back(Edge(b, l));
        edges[b].push_back(Edge(a, l));
    }
}

void dijkstra(int start)
{
    std::fill(dis, dis+n+1, inf);
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

void output(int casen)
{
    double maxedge = -1;
    int maxa, maxb;
    for (int i=1; i<=n; i++) {
        for (int j=0; j<edges[i].size(); j++) {
            int end = edges[i][j].end;
            int len = edges[i][j].len;
            if (abs(dis[i] - dis[end]) == len) continue;
            double tmp = (dis[i]+dis[end]+len) / 2.0;
            if (tmp > maxedge) {
                maxedge = tmp;
                maxa = i; maxb = end;
            } 
        }
    }
    double maxv = -1;
    int maxi;
    for (int i=1; i<=n; i++) {
        if (dis[i] > maxv) {
            maxv = dis[i];
            maxi = i;
        }
    }

    printf("System #%d\n", casen);
    if (maxedge > maxv+eps) {
        if (maxa > maxb) {
            std::swap(maxa, maxb);
        }
        printf("The last domino falls after %.1lf seconds, between key dominoes %d and %d.\n", maxedge, maxa, maxb);
    }
    else {
        printf("The last domino falls after %.1lf seconds, at key domino %d.\n", maxv, maxi);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    int casen = 1;
    while (scanf("%d%d", &n, &m), n) {
        input();
        dijkstra(1);
        output(casen++);
    }
    return 0;
}