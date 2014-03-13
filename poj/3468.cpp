#include <cstdio>

#define lson l, m, rt << 1
#define rson m+1, r, rt << 1 | 1

const int maxn = 100001;
long long sum[maxn << 2], mark[maxn << 2];

void push_up(int rt) {
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void push_down(int rt, int m) {
    if (mark[rt]) {
        mark[rt << 1] += mark[rt];
        mark[rt << 1|1] += mark[rt];
        sum[rt << 1] += (m-m/2) * mark[rt];
        sum[rt << 1|1] += (m>>1) * mark[rt];
        mark[rt] = 0;
    }
}

void update(int L, int R, int c, int l, int r, int rt) {
    if (L<=l && R>=r) {
        //mark[rt] = c;  this is wrong
        mark[rt] += c;
        sum[rt] += c * (r-l+1);
        return;
    }
    push_down(rt, r-l+1);
    int m = (l+r) >> 1;
    if (L <= m) update(L, R, c, lson);
    if (R > m)  update(L, R, c, rson);

    push_up(rt);
}

long long query(int L, int R, int l, int r, int rt) {
    if (L<=l && R>=r) {
        return sum[rt];
    }

    push_down(rt, r-l+1);//lazy
    int m = (l+r) >> 1;
    long long ret = 0;
    if (L<=m) ret += query(L, R, lson);
    if (R>m)  ret += query(L ,R, rson);

    return ret;
}

void build(int l, int r, int rt) {
    mark[rt] = 0;
    if (l == r) {
        scanf("%lld", &sum[rt]);
        return;
    }
    int m = (l+r) >> 1;
    build(lson);
    build(rson);
    push_up(rt);
}

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    build(1, n, 1);

    char op[2];
    int a, b, c;
    while (q--) {
        scanf("%s", op);
        if (op[0] == 'Q') {
            scanf("%d%d", &a, &b);
            printf("%lld\n", query(a, b, 1, n, 1));
        }
        else {
            scanf("%d%d%d", &a, &b, &c);
            update(a, b, c, 1, n, 1);
        }
    }
    return 0;
}
