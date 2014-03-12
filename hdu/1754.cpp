#include <cstdio>
#include <algorithm>
using namespace std;

#define lson l, m, rt << 1
#define rson m+1, r, rt << 1 | 1

const int maxn = 222222;
int sum[maxn << 2];

void push_up(int rt) {
    //how data pop up
    sum[rt] = max(sum[rt << 1], sum[rt << 1 | 1]);
}

void update(int p, int v, int l, int r, int rt) {
    if (l == r) {
        //how data update
        sum[rt] = v;
        return;
    }
    int m = (l+r) >> 1;
    if (p <= m) update(p, v, lson);
    else update(p, v, rson);

    push_up(rt);
}

int query(int L, int R, int l, int r, int rt) {
    if (L<=l && r<=R) {
        return sum[rt];
    }
    int m = (l+r) >> 1;
    int ret = 0;
    //how data query
    if (L <= m) ret = max(ret, query(L, R, lson));
    if (R > m)  ret = max(ret, query(L, R, rson));
    return ret;
}

void build(int l, int r, int rt) {
    if (l == r) {
        scanf("%d", &sum[rt]);
        return;
    }
    int m = (l+r) >> 1;
    build(lson);
    build(rson);
    push_up(rt);
}

int main()
{
    int N, M;
    char op[10];
    int a, b;
    while (~scanf("%d%d", &N, &M)) {
        build(1, N, 1);
        for (int i=0; i<M; i++) {
            scanf("%s%d%d", op, &a, &b);
            if (op[0] == 'Q') printf("%d\n", query(a, b, 1, N, 1));
            else update(a, b, 1, N, 1);
        }
    }
    return 0;
}
