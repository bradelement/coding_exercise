#include "cstdio"
#include "algorithm"
#include "vector"
using namespace std;

struct Edge
{
    int x, y, len;
    bool operator< (const Edge &e) const {
        return len < e.len || (len == e.len && make_pair(x, y) < make_pair(e.x, e.y));
    }
};

const int N = 101;
Edge hub[N*N];
int n, m, pre[N], put[N];

void input()
{
    scanf("%d", &n);
    int tmp;
    m = 0;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            scanf("%d", &tmp);
            if (tmp && i<j) {
                hub[m].x = i;
                hub[m].y = j;
                hub[m].len = tmp;
                m++;
            }
        }
    }
}

int find(int x)
{
    if (x == pre[x]) return x;
    return pre[x] = find(pre[x]);
}

void kruskal()
{
    vector<pair<int, int> > vp;
    int count = 0, maxlen = -1;
    for (int i=1; i<=n; i++) {
        pre[i] = i;
    }
    sort(hub, hub+m);

    for (int i=0; i<m; i++) {
        int a = find(hub[i].x);
        int b = find(hub[i].y);
        if (a!=b) {
            pre[b] = a;
            vp.push_back(make_pair(hub[i].x, hub[i].y));
        }
    }

    if (vp.size() == n-1) {
        sort(vp.begin(), vp.end());
        for (int i=0; i<vp.size(); i++) {
            if (i) printf(" ");
            printf("%d %d", vp[i].first, vp[i].second);
        }
        printf("\n");
    }
    else {
        printf("-1\n");
    }
}

int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);

    while (t--) {
        input();
        kruskal();
    }    
    return 0;
}