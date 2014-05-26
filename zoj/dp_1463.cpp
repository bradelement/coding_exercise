#include "cstdio"
#include "cstring"
using namespace std;

const int MAXN = 101;
char buf[MAXN];
char dp[MAXN][MAXN], mark[MAXN][MAXN];

char gao(int begin, int end) {
    if (dp[begin][end] == -1) {
        if (begin > end) return dp[begin][end] = 0;
        else if (begin == end) return dp[begin][end] = 1;

        dp[begin][end] = MAXN;
        int tmp;
        if ((buf[begin]=='('&&buf[end]==')') || \
            (buf[begin]=='['&&buf[end]==']')) {
            tmp = gao(begin+1, end-1);
            if (tmp < dp[begin][end]) {
                dp[begin][end] = tmp;
                mark[begin][end] = -1;    
            }
        }
        if (buf[begin]=='(' || buf[begin]=='[') {
            tmp = gao(begin+1, end)+1;
            if (tmp < dp[begin][end]) {
                dp[begin][end] = tmp;
                mark[begin][end] = begin;
            }
        }
        if (buf[end]==')' || buf[end]==']') {
            tmp = gao(begin, end-1)+1;
            if (tmp < dp[begin][end]) {
                dp[begin][end] = tmp;
                mark[begin][end] = end;
            }
        }

        for (int k=begin; k<=end-1; k++) {
            tmp = gao(begin, k)+gao(k+1, end);
            if (tmp < dp[begin][end]) {
                dp[begin][end] = tmp;
                mark[begin][end] = k;    
            }
        }
    }

    return dp[begin][end];
}

void print(int begin, int end) {
    if (begin > end) return;
    if (begin == end) {
        if (buf[begin] == '(' || buf[begin] == ')') {
            printf("()");
        }
        else {
            printf("[]");
        }
    }
    else if (mark[begin][end] == -1) {
        putchar(buf[begin]);
        print(begin+1, end-1);
        putchar(buf[end]);
    }
    else if (mark[begin][end] == begin) {
        if (buf[begin] == '(' || buf[begin] == ')') {
            printf("()");
        }
        else {
            printf("[]");
        }
        print(begin+1, end);
    }
    else if (mark[begin][end] == end) {
        print(begin, end-1);
        if (buf[end] == '(' || buf[end] == ')') {
            printf("()");
        }
        else {
            printf("[]");
        }
    }
    else {
        print(begin, mark[begin][end]);
        print(mark[begin][end]+1, end);
    }
}

int main(int argc, char const *argv[])
{
    int casen;
    scanf("%d", &casen);
    gets(buf);

    while (casen--) {
        gets(buf);
        gets(buf);
        int len = strlen(buf);
        memset(dp, -1, sizeof(dp));

        gao(0, len-1);
        print(0, len-1);
        puts("");
        if (casen) puts("");
    }

    return 0;
}
