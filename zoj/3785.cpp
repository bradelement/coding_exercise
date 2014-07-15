#include <cstdio>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

//i**i 循环节为42
const int MAGIC = 42;

char *s[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int r[MAGIC] = {1, 4, 6, 4, 3, 1, 0, 1, 1, 4, 2, 1, 6, 0, 1, 2, 5, 1, 5, 1, 0, 1, 4, 1, 4, 4, 6, 0, 1, 1, 3, 2, 6, 1, 0, 1, 2, 2, 1, 2, 6, 0};

int acc[MAGIC];
int main()
{
    int sum = 0;
    for (int i=0; i<42; i++) {
        sum += r[i];
        acc[i] = sum % 7;
    }
    sum %= 7;

    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int idx = (6 + (n-1)/42*sum + acc[(n-1)%42]) % 7;
        puts(s[idx]);
    }
    
    return 0;
}
