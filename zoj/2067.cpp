#include "cstdio"
#include "vector"
#include "algorithm"
#include "climits"
#include "cstring"
using namespace std;

const int MAXN = 101;
int n;
char board[MAXN][MAXN];
//how many continous white square from left
int dp[MAXN][MAXN];

int main(int argc, char const *argv[])
{
    while (~scanf("%d", &n)) {
        gets(board[0]);
        for (int i=0; i<n; i++) {
            gets(board[i]);
            dp[i][0] = board[i][0]=='.' ? 1:0;
            for (int j=1; j<n; j++) {
                if (board[i][j] == '.') {
                    dp[i][j] = dp[i][j-1] + 1;
                }
                else {
                    dp[i][j] = 0;
                }
            }
        }

        int ret = 0;
        int mn;
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                mn = dp[i][j];
                for (int k=i; k<n&&dp[k][j]>0; k++) {
                    if (dp[k][j] < mn) mn = dp[k][j];
                    ret += mn;
                }
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}