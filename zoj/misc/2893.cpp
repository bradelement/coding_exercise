#include "cstdio"
#include "cstring"
#include "cmath"

const int MAXN = 1<<18;
char a[MAXN], b[MAXN];

int log2(int n) {
    int cur = 0;
    int expo = 1;
    while (expo != n) {
        cur++;
        expo <<= 1;
    }
    return cur;
}

int nu(char *s) {
    int len = strlen(s);
    int ret = 0;
    for (int i=0; i<len; i++) {
        if (s[i] == '{') ret++;
    }
    return log2(ret);
}

void print(int num) {
    printf("{");
    for (int i=0; i<num; i++) {
        if (i) printf(",");
        print(i);
    }
    printf("}");
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    gets(a);

    while (n--) {
        gets(a);
        gets(b);
        print(nu(a)+nu(b));
        printf("\n");
    }
    return 0;
}