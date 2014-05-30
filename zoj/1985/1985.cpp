#include "iostream"
#include "stack"
#include "cstdio"
#include "vector"
using namespace std;

const int MAXN = 100002;
int a[MAXN], l[MAXN], r[MAXN];
vector<int> stk;

int main(int argc, char const *argv[])
{
    int n;
    while (scanf("%d", &n), n) {
        for (int i=1; i<=n; i++) {
            scanf("%d", &a[i]);
        }
        a[0] = a[n+1] = -1;

        stk.clear();
        stk.push_back(0);
        for (int i=1; i<=n; i++) {
            while (a[stk.back()] >= a[i]) stk.pop_back();
            l[i] = stk.back();
            stk.push_back(i);
        }

        stk.clear();
        stk.push_back(n+1);
        for (int i=n; i>=1; i--) {
            while (a[stk.back()] >= a[i]) stk.pop_back();
            r[i] = stk.back();
            stk.push_back(i);
        }

        long long ret = 0;
        long long tmp;
        for (int i=1; i<=n; i++) {
            tmp = (long long)a[i] * (r[i]-l[i]-1);
            if (tmp > ret) ret = tmp;
        }
        printf("%lld\n", ret);
    }

    return 0;
}