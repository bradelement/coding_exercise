#include <cstdio>
#include <cstring>

const int MAXN = 10001;
char s[MAXN];

int minP(char *in, int len) {
	int i=0, j=1, k=0, t;
	while (i<len && j<len && k<len) {
		t = s[(i+k) >= len ? i+k-len : i+k] - \
			s[(j+k) >= len ? j+k-len : j+k];
			
		if (t == 0) k++;
		else {
			if (t>0) i += k+1;
			else j += k+1;
			if (i == j) j++;
			k = 0;
		}
	}
	
	return i<j ? i:j;
	
}

int main()
{
	int n, len;
	scanf("%d", &n);
	while (n--) {
		scanf("%s", s);
		len = strlen(s);
		printf("%d\n", minP(s, len)+1);
	}
	
	return 0;
}