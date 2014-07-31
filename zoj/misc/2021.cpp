#include "cstdio"
#include "iostream"
#include "string"
#include "cstdlib"
#include "cstring"
#include "vector"
#include "set"
#include "map"
#include "algorithm"
using namespace std;

string reduce(const string &s, int cnt) {
    int cur=0, left, right;
    int i;
    for (left=0; left<s.length(); left++) {
        if (s[left] == '(' && ++cur == cnt) break;
    }
    cur = 0;
    for (right=left+1; right<s.length(); right++) {
        if (s[right] == ')') {
            if (cur == 0) break;
            cur--;
        }
        else if (s[right] == '(') {
            cur++;
        }
    }

    bool lok = false, rok = false;
    if (left-1 < 0 || s[left-1]=='+' || s[left-1]=='(') {
        lok = true;
    }
    else if (s[left-1] == '/') {
        for (i=left+1; i<right; i++) {
            if (s[i]=='(') {
                int cur = 0;
                i++;
                while (1) {
                    if (s[i]==')') {
                        if (cur == 0) break;
                        cur--;
                    }
                    else if (s[i] == '(') {
                        cur++;
                    }
                    i++;
                }
            }

            if (s[i]=='+' || s[i]=='-' || 
                s[i]=='*' || s[i]=='/') break;
        }
        if (i==right) lok = true;
    }
    else if (s[left-1] == '-' || s[left-1] == '*') {
        for (i=left+1; i<right; i++) {
            if (s[i]=='(') {
                int cur = 0;
                i++;
                while (1) {
                    if (s[i]==')') {
                        if (cur == 0) break;
                        cur--;
                    }
                    else if (s[i] == '(') {
                        cur++;
                    }
                    i++;
                }
            }

            if (s[i]=='+' || s[i]=='-') break;
        }
        if (i==right) lok = true;    
    }

    if (lok) {
        if (right+1 >= s.length() || s[right+1]=='+' || s[right+1]=='-' || s[right+1]==')') {
            rok = true;
        }
        else if (s[right+1] == '*' || s[right+1] == '/') {
            for (i=left+1; i<right; i++) {
                if (s[i]=='(') {
                int cur = 0;
                i++;
                while (1) {
                    if (s[i]==')') {
                        if (cur == 0) break;
                        cur--;
                    }
                    else if (s[i] == '(') {
                        cur++;
                    }
                    i++;
                }
            }
                
                if (s[i]=='+' || s[i]=='-') break;
            }
            if (i==right) rok = true;
        }
    }

    if (lok && rok) {
        string ret = s.substr(0, left) + \
            s.substr(left+1, right-left-1) + \
            s.substr(right+1);

        return ret;
    }
    return s;
}

string gao(string line) {
    int cnt = 0;
    for (int i=0; i<line.length(); i++) {
        if (line[i] == '(') cnt++;
    }

    for (int i=cnt; i>=1; i--) {
        line = reduce(line, i);
    }
    return line;
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    string line;
    while (n--) {
        cin >> line;
        cout << gao(line) << endl;
    }
    return 0;
}