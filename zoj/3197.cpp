#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
#include "algorithm"
#include "map"
#include "set"
using namespace std;

const int MAXN = 5005;
int T, N;
pair<int, int> a[MAXN];
int maxp[MAXN];

int main(int argc, char const *argv[])
{
    scanf("%d", &T);
    while (T--) {
        for (int i=1; i<=N; i++) {
            maxp[i] = i;
        }
        scanf("%d", &N);
        for (int i=1; i<=N; i++) {
            scanf("%d%d", &a[i].first, &a[i].second);
            if (a[i].second > maxp[a[i].first]) {
                maxp[a[i].first] = a[i].second;
            }
        }

        int cur = 0, prev = 1;
        int ans = 0;
        int mp = -1;
        do {
            for (int i=prev; i<=cur+1; i++) {
                if (maxp[i] > mp) mp = maxp[i];
            }
            ans++;
            prev = cur + 1;
            cur = mp;
        } while (cur < N);

        printf("%d\n", ans);

    }

    return 0;
}