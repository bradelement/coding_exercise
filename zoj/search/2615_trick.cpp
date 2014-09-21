#include "cstdio"
#include "cctype"

const int MAXN = 300001;
const int MAXR = 20000001;
int N, M;
int c[MAXN], pre[MAXN];
int stack[MAXR];
int top;
int in[MAXR], out[MAXR];

inline int get_num() {
    int ret = 0;
    char c = getchar();
    while (!isdigit(c)) c = getchar();
    do {
        ret = ret * 10 + c - '0';
        c = getchar();
    } while (isdigit(c));

    return ret;
}

void init() {
    //scanf("%d", &N);
    N = get_num();
    int tmp = 0;
    for (int i=0; i<N; i++) {
        //scanf("%d", &c[i]);
        c[i] = get_num();
        pre[i] = tmp;
        tmp += c[i];
    }
}

void dfs() {
    int tm = 0;
    stack[top = 0] = 0;
    in[0] = tm++;
    while (top >= 0) {
        int cur = stack[top];
        if (cur >= N || c[cur] == 0) {
            out[cur] = tm++;
            top--;
        }
        else {
            int child = pre[cur] + c[cur]--;
            in[child] = tm++;
            stack[++top] = child;
        }
    }
}

inline bool gao(int a, int b) {
    return in[a] < in[b] && out[a] > out[b];
}

int main(int argc, char const *argv[])
{
    int T = get_num();
    //scanf("%d", &T);
    for (int ci=1; ci<=T; ci++) {
        init();
        dfs();
        printf("Case %d:\n", ci);
        //scanf("%d", &M);
        M = get_num();
        int a, b;
        for (int i=0; i<M; i++) {
            //scanf("%d%d", &a, &b);
            a = get_num();
            b = get_num();
            puts(gao(a, b) ? "Yes" : "No");
        }
        if (ci != T) printf("\n");
    }
    return 0;
}