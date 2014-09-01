#include <cstdio>
#include <map>

int Z, I, M, L;
int gao() {
    std::map<int, int> mii;
    mii[L] = 0;
    int cur = L, loop_time = 0;
    while (1) {
        cur = (Z*cur + I) % M;
        loop_time++;
        if (mii.count(cur)) {
            return loop_time - mii[cur];
        }
        mii[cur] = loop_time;
    }
}

int main()
{
    int ci = 1;
    while (scanf("%d%d%d%d", &Z, &I, &M, &L), M) {
        printf("Case %d: %d\n", ci++, gao());
    }
    return 0;
}