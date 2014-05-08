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
    int len;
    scanf("%d", &casen);
    while (casen--) {
        scanf("%d", &n);
        len = 0;
        for (int i=0; i<n; i++) {
            scanf("%d", &t);
            if (len == 0) {
                last[len++] = t;
                continue;
            }

            if (t > last[len-1]) {
                last[len++] = t;
            }
            else {
                int ii=0, jj=len-1;
                while (ii<=jj) {
                    int mid = (ii+jj)/2;
                    last[mid] < t ? ii=mid+1 : jj=mid-1;
                }
                last[ii] = t;
            }
        }
        printf("%d\n", len);
    }

    return 0;
}