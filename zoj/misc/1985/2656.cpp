#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
using namespace std;

int N;

int main(int argc, char const *argv[])
{
    int a, b;
    int sum, start, partial_sum;
    while (~scanf("%d", &N)) {
        sum = partial_sum = 0;
        start = 0;
        for (int i=0; i<N; i++) {
            scanf("%d%d", &a, &b);
            sum += a - b;
            partial_sum += a - b;
            if (partial_sum < 0) {
                partial_sum = 0;
                start = i+1;
            }
        }

        if (sum < 0) {
            printf("impossible\n");
            continue;
        }
        printf("%d\n", start);
    }
    return 0;
}