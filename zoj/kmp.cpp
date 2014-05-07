#include "cstdio"
#include "cmath"
#include "string"
#include "iostream"
#include "stack"
#include "cstring"
#include "cassert"
using namespace std;

const int MAX_LEN = 1000005;

char A[MAX_LEN], B[MAX_LEN]; 
int next[MAX_LEN];

void deal_next(char B[], int m) {
    next[1] = 0;
    int j = 0;
    for (int i=2; i<=m; i++) {
        while (j>0 && B[j+1] != B[i]) j = next[j];
        if (B[j+1] == B[i]) j++;
        next[i] = j;
    }
}

/*
bool kmp(char A[], int n, char B[], int m) {
    deal_next(B, m);

    int j = 0;
    for (int i=1; i<=n; i++) {
        while (j>0 && B[j+1]!=A[i]) j = next[j];
        if (B[j+1] == A[i]) j++;
        if (j == m) {
            return true;
            //j = next[j]; //continue to match
        }
    }
    return false;
}
*/
int main(int argc, char const *argv[])
{
    while (~scanf("%s", A+1)) {
        if (strcmp(A+1, ".") == 0) break;
        int len = strlen(A+1);
        deal_next(A, len);
        if (len % (len - next[len]) == 0) printf("%d\n", len / (len - next[len]));
        else printf("1\n");
    }

    return 0;
}