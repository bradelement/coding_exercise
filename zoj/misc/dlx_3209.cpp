#include "cstdio"
#include "cstring"

const int M = 1005;
const int N = M*M;

int R[N], L[N], U[N], D[N], C[N];
int S[M];
int n, m;
int ans;
int size;

void init() {
    memset(S, 0, sizeof(S));

    for (int i=1; i<=m; i++) {
        L[i+1] = R[i-1] = U[i] = D[i] = i;
    }
    R[m] = 0;
    size = m+1;
}

void remove(int c) {
    R[L[c]] = R[c];
    L[R[c]] = L[c];
    for (int i=D[c]; i!=c; i=D[i]) {
        for (int j=R[i]; j!=i; j=R[j]) {
            U[D[j]] = U[j];
            D[U[j]] = D[j];
            S[C[j]]--;
        }
    }
}

void resume(int c) {
    for (int i=U[c]; i!=c; i=U[i]) {
        for (int j=L[i]; j!=i; j=L[j]) {
            U[D[j]] = D[U[j]] = j;
            S[C[j]]++;
        }
    }
    R[L[c]] = L[R[c]] = c;
}

void dfs(int k) {
    if (R[0] == 0) {
        if (ans == -1 || ans > k) ans = k;
        return;
    }
    int minm = M, c = -1;

    for (int i=R[0]; i; i=R[i]) {
        if (S[i]<minm) {
            minm = S[i];
            c = i;
        }
    }
    remove(c);
    for (int i=D[c]; i!=c; i=D[i]) {
        for (int j=R[i]; j!=i; j=R[j]) remove(C[j]);
        dfs(k+1);
        for (int j=L[i]; j!=i; j=L[j]) resume(C[j]);
    }
    resume(c);
}

void insertCol(int col) {
    C[size] = col;
    U[size] = U[col];
    D[U[col]] = size;
    U[col] = size;
    D[size] = col;
    S[col]++;
}

void insertRow(int &rowhead) {
    if (rowhead == -1) {
        L[size] = R[size] = size;
        rowhead = size;
    }
    else {
        L[size] = L[rowhead];
        R[L[rowhead]] = size;
        L[rowhead] = size;
        R[size] = rowhead;
    }
}

int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    while (t--) {
        int a, b;
        scanf("%d%d%d", &a, &b, &n);
        m = a*b;
        init();
        for (int i=1; i<=n; i++) {
            int x1, x2, y1, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            x1++, y1++;
            int rowhead = -1;
            for (int j=x1; j<=x2; j++) {
                for (int k=y1; k<=y2; k++) {
                    int col = j + (k-1)*a;
                    insertCol(col);
                    insertRow(rowhead);
                    size++;
                }
            }
        }
        ans = -1;
        dfs(0);
        printf("%d\n", ans);

    }
    return 0;
}
