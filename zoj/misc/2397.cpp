#include "cstdio"
#include "vector"
#include "cmath"
#include "algorithm"
#include "climits"
#include <functional>
#include "cstring"
using namespace std;

const int MAXN = 1000;
int tian[MAXN];
int king[MAXN];

int main(int argc, char const *argv[])
{
    int N;
    while (scanf("%d", &N), N) {
        for (int i=0; i<N; i++) {
            scanf("%d", &tian[i]);
        }
        for (int i=0; i<N; i++) {
            scanf("%d", &king[i]);
        }

        sort(tian, tian+N, greater<int>());
        sort(king, king+N, greater<int>());

        int front = 0, back = N-1;
        int ret = 0;
        for (int i=0,j=N-1; i<=j;) {
            if (tian[front] > king[i]) {
                ret += 200;
                front++;
                i++;
            }
            else if (tian[front] < king[i]) {
                ret -= 200;
                back--;
                i++;
            }
            else {
                if (tian[back] > king[j]) {
                    ret += 200;
                    back--;
                    j--;
                }
                else {
                    if (king[i] > tian[back]) {
                        ret -= 200;
                    }
                    back--;
                    i++;
                }
            }
        }
        printf("%d\n", ret);
    }

    return 0;
}