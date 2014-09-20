#include "cstdio"
#include "set"
#include "algorithm"
using namespace std;

const int MAXN = 300000;
bool prime[MAXN];

void gen() {
    fill(prime, prime+MAXN, true);
    for (int i=0; i<6; i++) {
        prime[i] = false;
    }
    for (int i=6; i<MAXN; i++) {
        if (!prime[i]) continue;
        int re = i % 7;
        if (re != 1 && re != 6) {
            prime[i] = false;
            continue;
        }
        int cur = i * 2;
        while (cur < MAXN) {
            prime[cur] = false;
            cur += i;
        }
    }
}

void gao(int n) {
    set<int> ans;
    for (int i=1, ano; i*i <= n; i++) {
        if (n % i == 0) {
            ano = n / i;
            if (prime[i]) {
                ans.insert(i);
            }
            if (prime[ano]) {
                ans.insert(ano);
            }
        }
    }
    printf("%d:", n);
    for (set<int>::iterator it=ans.begin(); it!=ans.end(); ++it) {
        printf(" %d", *it);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    gen();
    int n;
    while (scanf("%d", &n), n != 1) {
        gao(n);
    }
    return 0;
}