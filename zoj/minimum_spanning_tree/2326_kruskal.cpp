#include "cstdio"
#include "algorithm"
#include "map"
#include "string"
#include "iostream"
using namespace std;

struct Edge
{
    int x, y;
    double len;
    bool operator< (const Edge &e) const {
        return len < e.len;
    }
};

const int N = 1001;
Edge hub[N];
int n, m, pre[N];
double all_cable;
map<string, int> mi;

int find(int x)
{
    if (x == pre[x]) return x;
    return pre[x] = find(pre[x]);
}

void kruskal()
{
    double sum = 0;
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

    if (sum <= all_cable) {
        printf("Need %.1lf miles of cable\n", sum);
    }
    else {
        printf("Not enough cable\n");
    }
}

int main(int argc, char const *argv[])
{
    cin >> all_cable;
    cin >> n;
    for (int i=1; i<=n; i++) {
        string in;
        cin >> in;
        mi[in] = i;
    }
    cin >> m;
    string a, b;
    for (int i=1; i<=m; i++) {
        cin >> a >> b >> hub[i].len;
        hub[i].x = mi[a];
        hub[i].y = mi[b];
    } 
    kruskal();
    return 0;
}