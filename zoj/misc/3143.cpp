#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
#include "algorithm"
#include "map"
#include "set"
using namespace std;

typedef long long LL;
bool possible(LL n) {
    while (n%2 == 0) n/= 2;
    while (n%3 == 0) n/= 3;
    while (n%5 == 0) n/= 5;
    while (n%7 == 0) n/= 7;
    if (n >= 11) return false;
    return true;
}

LL next(LL n) {
    LL ret = 0;
    LL base = 1;
    do {
        for (int i=9; i>=2; i--) {
            if (n % i == 0) {
                ret += base * i;
                n /= i;
                base *= 10;
                break;
            }
        }
    } while (n != 1);

    return ret;
}

int main(int argc, char const *argv[])
{
    int casen;
    LL num;
    scanf("%d", &casen);
    while (casen--) {
        scanf("%lld", &num);
        if (!possible(num)) {
            puts("No sequence");
            continue;
        }

        int cnt = 0;
        printf("%lld", num);
        do {
            num = next(num);
            printf(" %lld", num);
            if (++cnt >= 9) break;
        } while (possible(num));
        printf("\n");
    }

    return 0;
}