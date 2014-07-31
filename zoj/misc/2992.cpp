#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

char s[256];

int find_match(char *s) {
    int cnt = 0, idx = 0;

    do {
        if (s[idx] == '[') cnt++;
        else if (s[idx] == ']') {
            cnt--;
            if (cnt == 0) return idx;
        }
        idx++;
    } while (1);
    return -1;
}

int gao(char *s, int len) {
    if (len == 0) return 0;
    if (len == 2) return 1;

    int j = find_match(s+1);
    int ret = 1 + gao(s+1, j+1);
    if (j+3 != len) {
        ret = max(ret, 1 + gao(s+j+2, len-j-3));
    }
    return ret;
}

int main()
{
    int n;
    scanf("%d", &n);
    gets(s);

    for (int i=1; i<=n; i++) {
        gets(s);
        int depth = gao(s, strlen(s));
        int ans = pow(2, depth);
        printf("%d %d\n", i, ans);
    }

    return 0;
}

