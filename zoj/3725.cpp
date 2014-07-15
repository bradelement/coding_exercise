#include <cstdio>
#include <cstring>

const int MAXN = 1e5 + 1;
const int MOD = 1e9 + 7;
int dp[MAXN];
int pow2[MAXN];
int main()
{
	pow2[0] = 1;
	for (int i=1; i<MAXN; i++) {
		pow2[i] = pow2[i-1] * 2;
		if (pow2[i] >= MOD) {
			pow2[i] -= MOD;
		}
	}

	int n, m;
	int a, b;
	while (~scanf("%d%d", &n, &m)) {
		memset(dp, 0, sizeof(int) * m);
		dp[m] = 1;
		for (int i=m+1; i<=n; i++) {
			//formula: dp[i] = dp[i-1] * 2 + pow2[i-1-m] - dp[i-1-m];
			a = dp[i-1] * 2;
			if (a >= MOD) a -= MOD;
			//because all these have already module MOD, this might be negative...
			b = pow2[i-1-m] - dp[i-1-m];
			if (b < 0) b += MOD;
			
			dp[i] = a + b;
			if (dp[i] >= MOD) dp[i] -= MOD;
			if (dp[i] < 0) dp[i] += MOD;
		}
		printf("%d\n", dp[n]);
	}

	return 0;
}