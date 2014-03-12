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
    s[rt] = s[rt << 1] + s[rt << 1 | 1];
}

void update(int p, int l, int r, int rt) {
    if (l == r) {
        //how data update
        s[rt]--;
        return;
    }
    int m = (l+r) >> 1;
    if (p <= m) update(p, lson);
    else update(p, rson);

    push_up(rt);
}

int query(int x, int l, int r, int rt) {
    if (l == r) {
        return l;
    }
    int m = (l+r) >> 1;
    //how data query
    int ret = (s[rt<<1] >= x) ? query(x, lson) : query(x-s[rt<<1], rson);
    return ret;
}

void build(int l, int r, int rt) {
    if (l == r) {
        s[rt] = 1;
        return;
    }
    int m = (l+r) >> 1;
    build(lson);
    build(rson);
    push_up(rt);
}

int pos[maxn], value[maxn], ans[maxn];

int main()
{
    while (~scanf("%d", &n)) {
        for (int i=1; i<=n; i++) {
            scanf("%d%d", &pos[i], &value[i]);
        }
        build(1, n, 1);

        for (int i=n; i>=1; i--) {
            int ret = query(pos[i]+1, 1, n, 1);
            update(ret, 1, n, 1);
            ans[ret] = value[i];
        }

        printf("%d", ans[1]);
        for (int i=2; i<=n; i++) {
            printf(" %d", ans[i]);
        }
        printf("\n");
    }

    return 0;
}
