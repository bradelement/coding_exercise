#include "cstdio"

int L, W, H;
int a[2], tmp;

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d%d", &L, &W, &H)) {
        a[0] = a[1] = 0;
        for (int i=0; i<L; i++) {
            for (int j=0; j<W; j++) {
                for (int k=0; k<H; k++) {
                    scanf("%d", &tmp);
                    a[(i+j+k) & 1] += tmp;
                }
            }
        }
        puts(a[0] == a[1] ? "Yes" : "No");
    }
    return 0;
}