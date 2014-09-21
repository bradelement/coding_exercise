#include "cstdio"
#include "unordered_map"
#include "string"
#include "algorithm"
using namespace std;

struct Edge
{
    int x, y, len;
    bool operator< (const Edge &e) const {
        return len < e.len;
    }
};

const int MAXM = 2001;
const int MAXN = 50001;
Edge hub[MAXN];
int pre[MAXM];
int M, N;
unordered_map<string, int> id;

int get_id(char *city) {
    unordered_map<string, int>::iterator it = id.find(city);
    if (it == id.end()) {
        int new_id = id.size()+1;
        id.insert(make_pair(city, new_id));
        return new_id;
    }
    else {
        return it->second;
    }
}

void init() {
    id.clear();
    scanf("%d%d", &M, &N);
    char c1[16], c2[16];
    for (int i=0; i<N; i++) {
        scanf("%s%s%d", c1, c2, &hub[i].len);
        hub[i].x = get_id(c1);
        hub[i].y = get_id(c2);
    }
}

int find(int x)
{
    if (x == pre[x]) return x;
    return pre[x] = find(pre[x]);
}

int kruskal() {
    for (int i=1; i<=M; i++) {
        pre[i] = i;
    }
    sort(hub, hub+N);

    int sum = 0;
    for (int i=0; i<N; i++) {
        int a = find(hub[i].x);
        int b = find(hub[i].y);
        if (a != b) {
            pre[b] = a;
            sum += hub[i].len;
        }
    }

    return sum;
}

int main(int argc, char const *argv[])
{
    int P;
    scanf("%d", &P);
    while (P--) {
        init();
        printf("%d\n", kruskal());
    }
    return 0;
}