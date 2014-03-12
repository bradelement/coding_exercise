#include <cstdio>
#include <algorithm>
using namespace std;

#define lson l, m, rt << 1
#define rson m+1, r, rt << 1 | 1

const int maxn = 222222;
int sum[maxn << 2];

void push_up(int rt) {
    //how data pop up
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void update(int p, int l, int r, int rt) {
    if (l == r) {
        //how data update
        sum[rt]++;
        return;
    }
    int m = (l+r) >> 1;
    if (p <= m) update(p, lson);
    else update(p, rson);

    push_up(rt);
}

int query(int L, int R, int l, int r, int rt) {
    if (L<=l && r<=R) {
        return sum[rt];
    }
    int m = (l+r) >> 1;
    int ret = 0;
    //how data query
    if (L <= m) ret += query(L, R, lson);
    if (R > m)  ret += query(L, R, rson);
    return ret;
}

void build(int l, int r, int rt) {
    if (l == r) {
        sum[rt] = 0;
        return;
    }
    int m = (l+r) >> 1;
    build(lson);
    build(rson);
    push_up(rt);
}

int x[maxn];
int main()
{
    int n;
    while (~scanf("%d", &n)) {
        build(0, n-1, 1); //pay attention to the boundary
        int s = 0;
        for (int i=0; i<n; i++) {
            scanf("%d", &x[i]);
            s += query(x[i], n-1, 0, n-1, 1);
            update(x[i], 0, n-1, 1);
        }
        int ret = s;
        for (int i=0; i<n; i++) {
            s += n - x[i] - x[i] - 1;
            ret = min(ret, s);
        }
        printf("%d\n", ret);
    }
    return 0;
}
