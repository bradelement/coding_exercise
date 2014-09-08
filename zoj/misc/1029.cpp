#include "cstdio"
#include "cstring"
#include "algorithm"
using namespace std;

const int MAXN = 200;
int N;
int cnt[MAXN];

void f(int x, int y) {
    int start = x / 2;
    int end = y / 2;
    for (int i=start; i<=end; i++) {
        cnt[i]++;
    }
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        memset(cnt, 0, sizeof(cnt));
        for (int i=0, x, y; i<N; i++) {
            scanf("%d%d", &x, &y);
            if (x > y) swap(x, y);
            f(x-1, y-1);
        }
        printf("%d\n", *max_element(cnt, cnt+200) * 10);
    }
    return 0;
}