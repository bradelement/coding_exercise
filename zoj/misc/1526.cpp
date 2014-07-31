#include "cstdio"
#include "cmath"

const double pi = acos(-1);
const double e = exp(1);
//数a的长度 = int(log10(a))+1 .......
//log10(n!) = log10(n) + log10(n-1) + ... + log10(1)
//斯特林公式    n! = sqrt(2*pi*n) * pow(n/e, n)
//log10(n!) = log10(sqrt(2*pi*n)) + n * log10(n/e)
int main(int argc, char const *argv[])
{
    int casen;
    scanf("%d", &casen);
    while (casen--) {
        int n, ans;
        scanf("%d", &n);
        ans = (int)(log10(sqrt(2*pi*n)) + n * log10(n / e)) + 1;
        printf("%d\n", ans);
    }
    return 0;
}