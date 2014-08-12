#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
using namespace std;

const int MAXN = 100002;
int a[MAXN];
long long sum[MAXN];

int l[MAXN], r[MAXN];
vector<int> stk;

int main(int argc, char const *argv[])
{
    int n;
    stk.reserve(MAXN);
    while (~scanf("%d", &n)) {
        sum[0] = 0;
        for (int i=1; i<=n; i++) {
            scanf("%d", &a[i]);
            sum[i] = sum[i-1] + a[i];
        }

        a[0] = a[n+1] = -1;

        stk.clear();
        stk.push_back(0);
        for (int i=1; i<=n; i++) {
            while (a[stk.back()] >= a[i]) stk.pop_back();
            l[i] = stk.back()+1;
            stk.push_back(i);
        }

        stk.clear();
        stk.push_back(n+1);
        for (int i=n; i>=1; i--) {
            while (a[stk.back()] >= a[i]) stk.pop_back();
            r[i] = stk.back()-1;
            stk.push_back(i);
        }

        long long ret = 0, tmp;
        int left, right;
        for (int i=1; i<=n; i++) {
            tmp = (sum[r[i]]-sum[l[i]-1]) * a[i];
            if (tmp > ret) {
                ret = tmp;
                left = l[i];
                right = r[i];
            }
        }
        printf("%lld\n", ret);
        printf("%d %d\n", left, right);
    }

    
    return 0;
}