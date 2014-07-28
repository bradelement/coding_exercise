#include "cstdio"
#include "algorithm"
#include "map"
#include "string"
#include "iostream"
using namespace std;

struct Edge
{
    int x, y, len;
    bool operator< (const Edge &e) const {
        return len < e.len;
    }
};

const int N = 1001;
Edge hub[N];
int n, m, pre[N];

int find(int x)
{
    if (x == pre[x]) return x;
    return pre[x] = find(pre[x]);
}

void kruskal()
{
    int sum = 0;
    for (int i=1; i<=n; i++) {
        pre[i] = i;
    }
    sort(hub, hub+m);

    for (int i=0; i<m; i++) {
        int a = find(hub[i].x);
        int b = find(hub[i].y);
        if (a!=b) {
            pre[b] = a;
            sum += hub[i].len;
        }
    }

    printf("%d\n", sum);
}

void input()
{
    int t;
    scanf("%d", &t);
    map<pair<int, int>, int> mp;
    int a, b, len;
    for (int i=0; i<t; i++) {
        scanf("%d%d%d", &a, &b, &len);
        if (a>b) {
            int tmp = a; a = b; b = tmp;
        }
        pair<int, int> tp = make_pair(a, b);
        if (mp.count(tp)) {
            if (len < mp[tp]) {
                mp[tp] = len;
            }
        }
        else {
            mp[tp] = len;
        }
    }
    m = 0;
    for (auto i=mp.begin(); i!=mp.end(); ++i) {
        hub[m].x = i->first.first;
        hub[m].y = i->first.second;
        hub[m].len = i->second;
        m++;
    }
}

int main(int argc, char const *argv[])
{
    while (scanf("%d", &n), n) {
        input();
        kruskal();
    }
    return 0;
}