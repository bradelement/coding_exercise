#include <cstdio>
#include <algorithm>
using namespace std;

#define lson l, m, rt << 1
#define rson m+1, r, rt << 1 | 1

const int maxn = 222222;
int s[maxn << 2];
int h, w, n, x;

void push_up(int rt) {
    //how data pop up
    s[rt] = max(s[rt << 1], s[rt << 1 | 1]);
}

void update(int p, int v, int l, int r, int rt) {
    if (l == r) {
        //how data update
        s[rt] += v;
        return;
    }
    int m = (l+r) >> 1;
    if (p <= m) update(p, v, lson);
    else update(p, v, rson);

    push_up(rt);
}

int query(int x, int l, int r, int rt) {
    if (l == r) {
        return l;
    }
    int m = (l+r) >> 1;
    //how data query
    int ret = (s[rt<<1] >= x) ? query(x, lson) : query(x, rson);
    return ret;
}

void build(int l, int r, int rt) {
    if (l == r) {
        s[rt] = w;
        return;
    }
    int m = (l+r) >> 1;
    build(lson);
    build(rson);
    push_up(rt);
}

int main()
{
    while (~scanf("%d%d%d", &h, &w, &n)) {
        if (h > n) h = n;
        build(1, h, 1);
        while (n--) {
            scanf("%d", &x);
            if (s[1] < x) puts("-1");
            else {
                int ret = query(x, 1, h, 1);
                printf("%d\n", ret);
                update(ret, -x, 1, h, 1);
            }
        }
    }

    return 0;
}
