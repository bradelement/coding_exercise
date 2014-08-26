#include "cstdio"
/*
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a%b);
}
*/
int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    int r = exgcd(b, a%b, x, y);
    int t = x;
    x = y;
    y = t - a/b*y;
    return r;
}

//求乘法逆元
//http://en.wikipedia.org/wiki/Modular_inverse
//ax === 1 (mod m)
int inv(int a, int m)
{
    int d, x, y;
    d = exgcd(a, m, x, y);
    if (d != 1) return -1; //无解
    return (x%m + m) % m;
}

int main(int argc, char const *argv[])
{
    int T, a, m, x, y;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &a, &m);
        int ans = inv(a, m);
        if (ans < 0) {
            puts("Not Exist");
        }
        else {
            //small positive number
            printf("%d\n", ans ? ans : ans+1);
        }
    }
    return 0;
}