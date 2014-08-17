#include "cstdio"

const int MAXN = 1024;
const int MAXT = 12;
const int inf = 0x12345678;
int N;
int T[MAXN];
int p[MAXN][MAXT];
int eaten[MAXN];

void input()
{
    scanf("%d", &N);
    for (int i=1; i<=N; i++) {
        scanf("%d", &T[i]);
        eaten[i] = 0;
        for (int j=0; j<T[i]; j++){
            scanf("%d", &p[i][j]);
        }
    }
}

void gao()
{
    int C=N, D=0;
    int min_milk, min_count, min_idx;
    int unchange_num = 0;
    for (int day=1; ; day++) {
        min_milk = inf;
        for (int i=1; i<=N; i++) {
            if (!eaten[i]) {
                int period = (day-1) % T[i];
                if (p[i][period] < min_milk) {
                    min_milk = p[i][period];
                    min_count = 1;
                    min_idx = i;
                }
                else if (p[i][period] == min_milk) {
                    min_count++;
                }
            }
        }

        if (C == 0) break;
        if (min_count == 1) {
            eaten[min_idx] = 1;
            C--;
            D = day;
            unchange_num = 0;
        }
        else {
            unchange_num++;
            // magic_num:2520 (1 - 10 的公倍数)
            //经测试 改到440也是可以ac~~ 大概快了3倍
            if (unchange_num >= 2520) break;
        }
    }

    printf("%d %d\n", C, D);
}

int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    while (t--) {
        input();
        gao();
    }
    return 0;
}