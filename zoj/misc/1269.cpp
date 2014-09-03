#include "cstdio"
#include "cmath"
using namespace std;

bool gao(int p, int n) {
    for (int i=0; i<p; i++) {
        if ((n-1) % p) return false;
        n = (n-1) / p * (p-1);
    }
    return n % p == 0;
}

int main(int argc, char const *argv[])
{
    int n, i;
    while (scanf("%d", &n), n>=0) {
        for (i=n; i>=2; i--) {//better way: 用n-1的约数 - -
            if (gao(i, n)) {
                printf("%d coconuts, %d people and 1 monkey\n", n, i);
                break;
            }
        }
        if (i < 2) {
            printf("%d coconuts, no solution\n", n);
        }
    }
    return 0;
}