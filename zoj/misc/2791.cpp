#include "cstdio"
#include "cstring"
#include "string"
using namespace std;

const int MAXN = 16;
char a[MAXN], b[MAXN];

int v(char c) {
    switch (c) {
    case 'm':
        return 1000;
    case 'c':
        return 100;
    case 'x':
        return 10;
    case 'i':
        return 1;
    default:
        return 0;
    }
}

int ston(const char *s) {
    int ret = 0;
    int cur = 1;
    while (*s) {
        if (*s >= '2' && *s <= '9') {
            cur = *s - '0';
        }
        else {
            ret += cur * v(*s);
            cur = 1;
        }
        s++;
    }
    return ret;
}

string ntos(int n) {
    string ret;
    int cur;
    while (n > 0) {
        if (n >= 1000) {
            cur = n / 1000;
            n %= 1000;
            if (cur > 1) ret.append(1, '0'+cur);
            ret.append(1, 'm');
        }
        else if (n >= 100) {
            cur = n / 100;
            n %= 100;
            if (cur > 1) ret.append(1, '0'+cur);
            ret.append(1, 'c');
        }
        else if (n >= 10) {
            cur = n / 10;
            n %= 10;
            if (cur > 1) ret.append(1, '0'+cur);
            ret.append(1, 'x');
        }
        else {
            if (n > 1) ret.append(1, '0'+n);
            ret.append(1, 'i');
            n = 0;
        }
    }
    return ret;
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s%s", a, b);
        int n = ston(a) + ston(b);
        puts(ntos(n).c_str());
    }
    return 0;
}