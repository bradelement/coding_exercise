#include "iostream"
#include "stack"
#include "cstdio"
using namespace std;

const int MAXN = 100001;
int h[MAXN];

int main(int argc, char const *argv[])
{
    int n;
    while (scanf("%d", &n), n) {
        for (int i=0; i<n; i++) {
            scanf("%d", &h[i]);
        }
        h[n] = 0;
        stack<int> si;
        
        int i = 0;
        long long ret = 0;
        while (i < n+1) {
            if (si.empty() || h[si.top()] <= h[i]) {
                si.push(i++);
            }
            else {
                int t = si.top(); si.pop();
                long long tmp = (long long)h[t] * (si.empty()?i:i-si.top()-1);
                if (tmp > ret) ret = tmp;
            }
        }
        printf("%lld\n", ret);
    }

    return 0;
}