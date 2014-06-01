#include <cstdio>
#include <algorithm>
using namespace std;
 
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1

const int maxn = 11111;
int add[maxn<<2];
int sum[maxn<<2];

void PushUp(int rt) {
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}
void PushDown(int rt,int m) {
    if (add[rt]) {
        add[rt<<1] += add[rt];
        add[rt<<1|1] += add[rt];
        sum[rt<<1] += add[rt] * (m - (m >> 1));
        sum[rt<<1|1] += add[rt] * (m >> 1);
        add[rt] = 0;
    }
}
void build(int l,int r,int rt) {
    add[rt] = sum[rt] = 0;
    if (l == r) {
        return;
    }
    
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    //PushUp(rt);
}
void update(int L,int R,int c,int l,int r,int rt) {
    if (L <= l && r <= R) {
        add[rt] += c;
        sum[rt] += c * (r - l + 1);
        return ;
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , c , lson);
    if (m < R) update(L , R , c , rson);
    PushUp(rt);
}
int query(int L,int R,int l,int r,int rt) {
    if (L <= l && r <= R) {
        return sum[rt];
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m) ret += query(L , R , lson);
    if (m < R) ret += query(L , R , rson);
    return ret;
}
int main() {
    int T, N;
    int a, b;
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d", &N);
        build(1 , 10001 , 1);

        for (int i=0; i<N; i++) {
            scanf("%*d%d%d", &a, &b);
            update(a+1 , b+1 , 1 , 1 , 10001 , 1);    
        }
        
        int maxret = 0;
        int tmp;
        for (int i=0; i<=10000; i++) {
            tmp = query(i+1, i+1, 1, 10001, 1);
            //printf("i[%d], v[%d]\n", i+1, tmp);
            if (tmp > maxret) maxret = tmp;
        }
        printf("%d\n", maxret);
    }
    return 0;
}
