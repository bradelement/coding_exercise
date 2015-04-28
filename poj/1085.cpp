#include <cstdio>

int mat[11][11] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 2, 3, 4, 0, 0, 0, 0, 0},
    {0, 1, 2, 0, 0, 5, 6, 0, 0, 0, 0},
    {0, 0, 3, 0, 0, 7, 0, 9, 10, 0, 0},
    {0, 0, 4, 5, 7, 0, 8, 0, 11, 12, 0},
    {0, 0, 0, 6, 0, 8, 0, 0, 0, 13, 14},
    {0, 0, 0, 0, 9, 0, 0, 0, 15, 0, 0},
    {0, 0, 0, 0, 10, 11, 0, 15, 0, 16, 0},
    {0, 0, 0, 0, 0, 12, 13, 0, 16, 0, 17},
    {0, 0, 0, 0, 0, 0, 14, 0, 0, 17, 0},
};
//base on above, every edge has a number.
int tri[] = {7,152,52,352,34304,3200,71680,12544,155648};
int STATUS = (1<<18) - 1;

int get_status(int old, int seg, int &cnt) {
    int now = old | seg;
    for (int i=0; i<9; i++) {
        if ((old&tri[i])!=tri[i] && (now&tri[i])==tri[i]) {
            cnt++;
        }
    }
    return now;
}

int MaxSearch(int state, int alpha, int ca, int cb);
int MinSearch(int state, int beta, int ca, int cb)
{
    if (ca >= 5) return 1;
    if (cb >= 5) return -1;
    if (state == STATUS) return ca > cb ? 1 : -1;

    int ans = 1, tmp;
    int remain = (~state) & STATUS;
    while (remain) {
        int seg = remain & (-remain);
        int ta=ca, tb=cb;
        int now = get_status(state, seg, tb);
        if (tb > cb) tmp = MinSearch(now, beta, ca, tb);
        else tmp = MaxSearch(now, ans, ca, tb);

        if (tmp < ans) ans = tmp;

        if (tmp <= beta) return ans;
        remain -= seg;
    }

    return ans;
}

int MaxSearch(int state, int alpha, int ca, int cb)
{
    if (ca >= 5) return 1;
    if (cb >= 5) return -1;
    if (state == STATUS) return ca>cb ? 1 : -1;

    int ans = -1, tmp;
    int remain = (~state) & STATUS;
    while (remain) {
        int seg = remain & (-remain);
        int ta=ca, tb=cb;
        int now = get_status(state, seg, ta);

        if (ta > ca) tmp = MaxSearch(now, alpha, ta, cb);
        else tmp = MinSearch(now, ans, ta, cb);

        if (tmp > ans) ans = tmp;

        if (tmp >= alpha) return ans;
        remain -= seg;
    }

    return ans;
}

bool gao()
{
    int n;
    scanf("%d", &n);

    int cnt=0, state=0;
    int ca=0, cb=0, u, v;
    while (n--) {
        scanf("%d%d", &u, &v);
        int ta=ca, tb=cb;
        state = get_status(state, 1<<mat[u][v], (cnt&1)?cb:ca);

        if (ta==ca && tb==cb) cnt++;
    }

    int ans;
    if (cnt & 1) {
        ans = MinSearch(state, -1, ca, cb);
    }
    else {
        ans = MaxSearch(state, 1, ca, cb);
    }

    return ans == 1;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int t=1; t<=T; t++) {
        printf("Game %d: %c wins.\n", t, gao() ? 'A' : 'B');
    }

    return 0;
}
