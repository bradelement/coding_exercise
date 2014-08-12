#include "iostream"
#include "stack"
#include "cstdio"
using namespace std;

const int MAXN = 100001;
int w[MAXN];
int h[MAXN];

int main(int argc, char const *argv[])
{
    int n;
    while (scanf("%d", &n), n!=-1) {
        for (int i=0; i<n; i++) {
            scanf("%d%d", &w[i], &h[i]);
            if (i) w[i] += w[i-1];
        }
        h[n] = 0;
        stack<int> si;
        
        int i = 0;
        int ret = 0;
        while (i < n+1) {
            if (si.empty() || h[si.top()] <= h[i]) {
                si.push(i++);
            }
            else {
                int t = si.top(); si.pop();
                int width = si.empty() ? w[i-1] : w[i-1]-w[si.top()];
                int height = h[t];
                int tmp = height * width;
                if (tmp > ret) ret = tmp;
            }
        }
        printf("%d\n", ret);
    }

    return 0;
}