#include <cstdio>
#include <algorithm>
using namespace std;

#define lson l, m, rt << 1
#define rson m+1, r, rt << 1 | 1

const int maxn = 200002;
int sum[maxn << 2];
int tmp;

void push_up(int rt) {
    //how data pop up
    //sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void update(int p, int l, int r, int rt) {
    sum[rt]--;
    if (l == r) {
        //how data update
        tmp = l;
        return;
    }
    int m = (l+r) >> 1;
    if (sum[rt<<1] >= p) update(p, lson);
    else update(p-sum[rt<<1], rson);

    return;
}

int query(int n, int l, int r, int rt) {
    if (l == r) {
        return l;
    }
    int m = (l+r) >> 1;
    //how data query
    int ret = 0;
    ret = (n<=sum[rt << 2]) ? query(n, lson) : query(n, rson);
    return ret;
}

void build(int l, int r, int rt) {
    sum[rt] = r - l + 1;
    if (l == r) {
        return;
    }
    int m = (l+r) >> 1;
    build(lson);
    build(rson);
    //push_up(rt);
}

int pos[maxn], value[maxn], ans[maxn];
int main()
{
    int n;
    while (~scanf("%d", &n)) {
        for (int i=1; i<=n; i++) {
            scanf("%d%d", &pos[i], &value[i]);
        }
        build(1, n, 1);

        for (int i=n; i>=1; i--) {
            update(pos[i]+1, 1, n, 1);
            ans[tmp] = value[i];
        }
        printf("%d", ans[1]);
        for (int i=2; i<=n; i++) {
            printf(" %d", ans[i]);
        }
        puts("");
    }
    return 0;
}
