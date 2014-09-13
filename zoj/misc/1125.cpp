#include "cstdio"
#include "cmath"
#include "cstdlib"

char line[20];

int cal(int start, int end) {
    int ret = 0;
    for (int i=start; i<=end; i++) {
        ret = ret * 2 + line[i] - '0';
    }
    return ret;
}

void print(double n) {
    if (n == 0) {
        puts(" 0.000000e+000");
        return;
    }
    char sign = (n > 0 ? ' ' : '-');
    n = fabs(n);
    int exponent = 0;
    while (n >= 10) {
        n /= 10;
        exponent++;
    }
    while (n < 1) {
        n *= 10;
        exponent--;
    }
    
    char esign = (exponent >= 0 ? '+' : '-');
    printf("%c%.6lfe%c%03d\n", sign, n, esign, abs(exponent));
}

void gao() {
    int sign = (line[0] == '1' ? -1 : 1);
    int exponent = cal(1, 7);
    int mantissa = cal(8, 15);

    if (exponent==0 && mantissa==0) {
        print(0);
        return;
    }

    double num = sign * (1+mantissa/256.0) * pow(2, exponent-63);
    print(num);
}

int main(int argc, char const *argv[])
{
    puts("Program 6 by team X");
    while (gets(line)) {
        gao();
    }
    puts("End of program 6 by team X");
    return 0;
}