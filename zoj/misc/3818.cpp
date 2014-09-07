#include "cstdio"
#include "cstring"
#include "cstdlib"
#include "iostream"
#include "string"
#include "vector"
using namespace std;

bool eq5(const string &s, int alen, int blen) {
    string a = s.substr(0, alen);
    string b = s.substr(alen, blen);
    return a != b && s.substr(alen+blen, alen) == a && s.substr(2*(alen+blen), alen) == a && s.substr(2*alen+blen, blen) == b;
}

bool gao5(const string &s) {
    if (s.length() < 5) return false;
    int alen = 1, blen;
    while (1) {
        int tot = s.length() - 3*alen;
        if (tot <= 0) return false;
        if (tot & 1) {
            alen++;
            continue;
        }
        blen = tot / 2;
        if (eq5(s, alen, blen)) return true;
        alen++;
    }
    return false;
}

bool eq7(const string &s, int len) {
    string ab = s.substr(0, len);
    if (s.substr(len, len) != ab || s.substr(s.length()-len, len) != ab) return false;
    string c = s.substr(2*len, s.length()-3*len);
    for (int i=1; i<len; i++) {
        string a = s.substr(0, i);
        string b = s.substr(i, len-i);
        if (a != b && a != c && b != c) return true;
    }
    return false;
}

bool gao7(const string &s) {
    if (s.length() < 7) return false;
    int ablen = 2, clen;
    while (1) {
        clen = s.length() - 3*ablen;
        if (clen <= 0) return false;
        if (eq7(s, ablen)) return true;
        ablen++;
    }
    return false;
}

bool gao(const string &s) {
    return gao5(s) || gao7(s);
}

char line[64];

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    gets(line);
    while (T--) {
        gets(line);
        string poem;
        for (int i=0; line[i]; i++) {
            if (isalpha(line[i])) {
                poem += (line[i]);
            }
        }
        puts(gao(poem) ? "Yes" : "No");
    }
    return 0;
}