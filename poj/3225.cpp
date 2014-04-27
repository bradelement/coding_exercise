#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define lson l, m, rt << 1
#define rson m+1, r, rt << 1|1

const int maxn = 66000;
bool hash[maxn];
int cover[maxn << 2];
int XOR[maxn << 2];

void FXOR(int rt) {
    if (cover[rt] != -1) cover[rt] ^= 1;
    else XOR[rt] ^= 1;
}

void PushDown(int rt) {
    if (cover[rt] != -1) {
        cover[rt<<1] = cover[rt<<1|1] = cover[rt];
        cover[rt] = -1;
        XOR[rt<<1] = XOR[rt<<1|1] = 0;
    }
    if (XOR[rt]) {
        FXOR(rt << 1);
        FXOR(rt << 1|1);
        XOR[rt] = 0;
    }
}

void update(char op, int L, int R, int l, int r, int rt) {
    if (L<=l && R>=r) {
        if (op == 'U') {
            cover[rt] = 1;
            XOR[rt] = 0;
        }
        else if (op == 'D') {
            cover[rt] = 0;
            XOR[rt] = 0;
        }
        else if (op == 'C' || op == 'S') {
            FXOR(rt);
        }
        return;
    }
    PushDown(rt);

    int m = (l+r) >> 1;
    if (L<=m) update(op, L, R, lson);
    else if (op == 'I' or op == 'C') {
        XOR[rt<<1] = cover[rt<<1] = 0;
    }
    if (R>m)  update(op, L, R, rson);
    else if (op == 'I' or op == 'C') {
        XOR[rt<<1|1] = cover[rt<<1|1] = 0;
    }
}

void query(int l, int r, int rt) {
    if (cover[rt] != -1) {
        for (int i=l; i<=r; i++) {
            hash[i] = true;
        }
        return;
    } else if (cover[rt] == 0) return;

    PushDown(rt);
    int m = (l+r) >> 1;
    query(lson);
    query(rson);
}

int main()
{
    int c, n;
    scanf("%d", &c);
    while (c--) {
        scanf("%d", &n);
        int nn = 0;
        for (int i=0; i<n; i++) {
            scanf("%d%d", li+i, ri+i);
            X[nn++] = li[i];
            X[nn++] = ri[i];
        }
        sort(X, X+nn);
        int m = 1;
        for (int i=1; i<nn; i++) {
            if (X[i] != X[i-1]) X[m++] = X[i];
        }
        for (int i=m-1; i>0; i--) {
            if (X[i] != X[i-1]+1) X[m++] = X[i-1]+1;
        }
        sort(X, X+m);
        memset(col, -1, sizeof(col));

        for (int i=0; i<n; i++) {
            int l = Bin(li[i], m, X);
            int r = Bin(ri[i], m, X);
            update(l, r, i, 0, m-1, 1);
        }
        cnt = 0;
        memset(hash, false, sizeof hash);
        query(0, m-1, 1);
        printf("%d\n", cnt);
    }

    return 0;
}
