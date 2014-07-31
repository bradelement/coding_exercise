#include "cstdio"
#include "cmath"
#include "string"
#include "iostream"
#include "stack"
#include "cstring"
#include "cassert"
using namespace std;

const int MAX_SLEN = 512001;
int next[MAX_SLEN];
int num[MAX_SLEN];
char text[MAX_SLEN];
char pat[257];

void deal_next(char B[], int m) {
    next[1] = 0;
    int j = 0;
    for (int i=2; i<=m; i++) {
        while (j>0 && B[j+1] != B[i]) j = next[j];
        if (B[j+1] == B[i]) j++;
        next[i] = j;
    }
}


int kmp(char A[], int n, char B[], int m) {
    int ans = 0;

    deal_next(B, m);
    int j = 0;

    stack<int> si;
    for (int i=1; i<=n; i++) {
        si.push(i);
        while (j>0 && B[j+1]!=A[i]) j = next[j];
        if (B[j+1] == A[i]) j++;
        num[i] = j;
        if (j == m) {
            ans++;
            for (int i=0; i<m; i++) si.pop();
            if (si.empty()) j = 0;
            else j = num[si.top()];
            //return true;
            //j = next[j]; //continue to match
        }
    }
    return ans;
}

int main(int argc, char const *argv[])
{
    while (~scanf("%s%s", pat+1, text+1)) {
        int pLen = strlen(pat+1);
        int tLen = strlen(text+1);
        printf("%d\n", kmp(text, tLen, pat, pLen));
    }

    return 0;
}