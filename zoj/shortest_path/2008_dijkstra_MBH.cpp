#include "cstdio"
#include "cstring"
#include "vector"
#include "functional"
#include "algorithm"
#include "queue"
#include "unordered_map"
using namespace std;

template <int SZ, class T=int, class Op=less<T> >
class MBH {
    pair<int, T> heap[SZ+1];
    int key[SZ+1], sz;

public:
    void clear() {
        sz = 0; memset(key, 0, sizeof(key));
    }

    bool empty() const {
        return sz == 0;
    }

    pair<int, T> top() const {
        return heap[1];
    }

    void push(int idx, T val) {
        if (!key[idx]) {
            key[idx] = ++sz;
            heap[sz] = make_pair(idx, val);
        }
        else if (Op()(val, heap[key[idx]].second)) {
            heap[key[idx]].second = val;
        }

        for (int pos=key[idx], c; (c=pos>>1)&&Op()(val, heap[c].second);
            pos = c) {

            swap(heap[pos], heap[c]);
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
                swap(heap[c], heap[pos]);
                key[heap[c].first] = c;
                key[heap[pos].first] = pos;
            }
            else break;
        }
    }


};

const int MAXN = 1e6 + 1;
const int inf = 1e9+1;
int P, Q;
struct Edge {
    int id, weight;
    Edge(int a=0, int b=0): id(a), weight(b) {}

    bool operator< (const Edge &e) const {
        return weight > e.weight;
    }
};

std::unordered_map<int, std::vector<Edge> > ve[2];
int dis[MAXN];
MBH<MAXN> hp;

void input()
{
    for (int i=1; i<=P; i++) {
        ve[0][i].clear();
        ve[1][i].clear();
    }

    int a, b, c;
    scanf("%d%d", &P, &Q);
    for (int i=0; i<Q; i++) {
        scanf("%d%d%d", &a, &b, &c);
        ve[0][a].push_back(Edge(b, c));
        ve[1][b].push_back(Edge(a, c));
    }
}

int dijkstra(int idx)
{
    int start = 1;
    std::fill(dis, dis+P+1, inf);
    dis[start] = 0;
    hp.clear();
    hp.push(start, 0);

    while (!hp.empty()) {
        int now = hp.top().first;
        hp.pop();

        for (int i=0; i<ve[idx][now].size(); i++) {
            Edge &e = ve[idx][now][i];
            if (dis[e.id] > dis[now]+e.weight) {
                dis[e.id] = dis[now]+e.weight;
                hp.push(e.id, dis[e.id]);
            }
        }
    }
    
    int ret = 0;
    for (int i=1; i<=P; i++) ret += dis[i];
    return ret;
}

int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    while (t--) {
        input();
        printf("%d\n", dijkstra(0)+dijkstra(1));
    }

    return 0;
}