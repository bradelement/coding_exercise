#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
#include "algorithm"
#include "map"
#include "set"
using namespace std;

const int MAXN = 100000;
int mem_cnt[MAXN];

int cnt(int n) {
    if (mem_cnt[n]) return mem_cnt[n];

    if (n <= 9) return mem_cnt[n] = n;
    if (n <= 99) return mem_cnt[n] =(n-9)*2 + cnt(9);
    if (n <= 999) return mem_cnt[n] =(n-99)*3 + cnt(99);
    if (n <= 9999) return mem_cnt[n] =(n-999)*4 + cnt(999);
    return mem_cnt[n] =(n-9999)*5 + cnt(9999);
}

int nth_num(int num, int nth) {
    int vi[10];
    int cnt = 0;
    do {
        vi[cnt++] = num % 10;
        num /= 10;
    } while (num);

    return vi[cnt-1-nth];
}

int gao(int cur) {
    if (cur <= 9) return cur;
    if (cur <= cnt(99)) {
        cur -= 9+1;
        int nth = cur % 2;
        int num = 10 + cur/2;
        return nth_num(num, nth);
    }    
    if (cur <= cnt(999)) {
        cur -= cnt(99)+1;
        int nth = cur % 3;
        int num = 100 + cur / 3;
        return nth_num(num, nth);
    }
    if (cur <= cnt(9999)) {
        cur -= cnt(999)+1;
        int nth = cur % 4;
        int num = 1000 + cur / 4;
        return nth_num(num, nth);
    }

    cur -= cnt(9999)+1;
    int nth = cur % 5;
    int num = 10000 + cur / 5;
    return nth_num(num, nth);
}

int main(int argc, char const *argv[])
{
    int n;

    while (~scanf("%d", &n)) {
        int len = cnt(n);

        bool delete_even = true;
        int cur = len;
        int count = 0;
        while (cur != 1) {
            if (delete_even) {
                if (cur & 1) {
                    cur /= 2;
                    cur++;
                }
                else {
                    cur /= 2;
                }

            }
            else {
                cur /= 2;
            }
            if (cur != 1) delete_even = !delete_even;
            count++;
        }

        while (count--) {
            if (delete_even) {
                cur *= 2;
                cur--;
            }
            else {
                cur *= 2;
            }
            delete_even = !delete_even;
        }

        printf("%d\n", gao(cur));
    }

    return 0;
}