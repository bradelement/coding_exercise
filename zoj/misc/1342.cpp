#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int c(int n, int m) {
    int ret = 1;
    for (int i=0; i<m; i++) {
        ret *= n-i;
    }
    for (int i=1; i<=m; i++) {
        ret /= i;
    }
    return ret;
}
string make(char c, int len) {
    string ret;
    for (int i=0; i<len; i++) {
        ret += c + 1 + i;
    }
    return ret;
}

int gao(string s) {
    if (s.length() == 0) {
        return 0;
    }
    
    int ret = 0;
    for (int i=1; i<s.length(); i++) {
        ret += c(26, i);
    }
    for (int i='a'; i<s[0]; i++) {
        ret += c(26 - (i-'a'+1), s.length()-1);
    }
    return ret + gao(s.substr(1)) - gao(make(s[0], s.length()-1));
}

int main()
{
    string s;
    while (cin >> s) {
        bool valid = true;
        for (int i=1; i<s.length(); i++) {
            if (s[i] <= s[i-1]) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            cout << 0 << endl;
            continue;
        }

        cout << gao(s) + 1 << endl;
    }
    return 0;
}
