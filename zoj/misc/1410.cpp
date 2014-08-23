#include "cstdio"
#include "cmath"
#include "vector"
using namespace std;

const int MAXN = (sqrt(2147483647.0) + 1) * 2;

int ipow(int a, int n) {
    int ret = 1;
    while (n--) {
        ret *= a;
    }
    return ret;
}

long long lower_search(int n) {
    long long sum = 0, len = 1, digit = 9;
    int cur_len = 0;
    while (sum < n) {
        cur_len += len;
        sum += cur_len;
        if (sum >= n) return sum - cur_len;
        if (--digit == 0) {
            len++;
            digit = 9 * ipow(10, len-1);
        }
    }
    return 0;
}

int gao3(int n, int m) {
    vector<int> d;
    do {
        d.push_back(n % 10);
        n /= 10;
    } while (n);
    return d[d.size()-1-m];
}

int gao2(int n) {
    int count = 9, digit = 1;
    while (n > count) {
        n -= count;
        digit++;
        count = 9 * ipow(10, digit-1) * digit;
    }
    return gao3((n-1)/digit + ipow(10, digit-1), (n-1)%digit);

}

void gao(int n) {
    n -= lower_search(n);
    printf("%d\n", gao2(n));
}

int main(int argc, char const *argv[])
{
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        gao(n);
    }
    return 0;
}