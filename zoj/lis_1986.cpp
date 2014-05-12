#include <cstdio>
#include "iostream"
#include <algorithm>
#include <cmath>
#include "climits"
using namespace std;

const int MAXN = 40001;
int n;
int last[MAXN];

int main(int argc, char const *argv[])
{
    int casen, t;
    scanf("%d", &casen);
    while (casen--) {
        scanf("%d", &n);
        fill(last, last+n, INT_MAX);
        for (int i=0; i<n; i++) {
            scanf("%d", &t);
            *lower_bound(last, last+n, t) = t;
        }
        printf("%d\n", lower_bound(last, last+n, INT_MAX)-last);
    }

    return 0;
}