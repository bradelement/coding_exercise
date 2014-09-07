#include "cstdio"

int h[64];

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    int N;
    while (T--) {
        scanf("%d", &N);
        for (int i=0; i<N; i++) {
            scanf("%d", &h[i]);
        }
        int ans = 0;
        for (int i=1; i<N-1; i++) {
            if (h[i] > h[i-1] && h[i] > h[i+1]) ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}