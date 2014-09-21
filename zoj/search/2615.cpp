#include "cstdio"
#include "stack"

const int MAXN = 300001;
const int MAXR = 20000001;
int N, M;
int c[MAXN], pre[MAXN];
std::stack<int> si;
int in[MAXR], out[MAXR];

void init() {
    scanf("%d", &N);
    int tmp = 0;
    for (int i=0; i<N; i++) {
        scanf("%d", &c[i]);
        pre[i] = tmp;
        tmp += c[i];
    }
}

void dfs() {
    int tm = 0;
    si.push(0);
    in[0] = tm++;
    while (!si.empty()) {
        int cur = si.top();
        if (cur >= N || c[cur] == 0) {
            out[cur] = tm++;
            si.pop();
        }
        else {
            int child = pre[cur] + c[cur]--;
            in[child] = tm++;
            si.push(child);
        }
    }
}

inline bool gao(int a, int b) {
    return in[a] < in[b] && out[a] > out[b];
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    for (int ci=1; ci<=T; ci++) {
        init();
        dfs();
        printf("Case %d:\n", ci);
        scanf("%d", &M);
        int a, b;
        for (int i=0; i<M; i++) {
            scanf("%d%d", &a, &b);
            puts(gao(a, b) ? "Yes" : "No");
        }
        if (ci != T) printf("\n");
    }
    return 0;
}