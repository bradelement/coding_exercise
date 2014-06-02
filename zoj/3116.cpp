#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
#include "algorithm"
#include "map"
#include "set"
using namespace std;

const int MAXN = 10001;
int N, L;
pair<int, int> a[MAXN];
int R[MAXN];

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d", &N, &L)) {
        for (int i=0; i<N; i++) {
            scanf("%d%d", &a[i].first, &a[i].second);
        }
        if (N == 0 || L == 0) {
            printf("0\n");
            continue;
        }
        
        fill(R, R+MAXN, L);
        sort(a, a+N);
        int ans = 0;

        for (int i=N-1; i>=0; i--) {
            int P = a[i].second;
            while (P >= 0 && R[P] == 0) P--;
            if (P >= 0) {
                R[P]--;
                ans += a[i].first;
            }
        }
        printf("%d\n", ans);
    }
    
    return 0;
}