#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

int N;
char line[6][16];
char to[4];

string add_one(char a, char b, int &carry) {
    string ret = "0";
    int aa = a - '0', bb = b - '0';
    int r = aa + bb + carry;
    if (r >= 4) {
        r -= 4;
        carry = 1;
    }
    else {
        carry = 0;
    }
    ret[0] = '0' + r;
    return ret;
}

string _add(string num1, string num2, int &carry)
{
    if (carry == 1) {
        int tc = 0;
        if (num1 == "") {
            return _add("1", num2, tc);
        }
        else if (num2 == "") {
            return _add(num1, "1", tc);
        }
    }
    else {
        if (num1 == "") return num2;
        else if (num2 == "") return num1;
    }
    string c = add_one(num1[0], num2[0], carry);
    return c + _add(num1.substr(1), num2.substr(1), carry);
}

string s_to_f(string num) {
    string ret;
    for (int i=0; i<num.length(); i++) {
        for (int j=0; j<4; j++) {
            if (num[i] == to[j]) {
                ret.append(1, '0'+j);
                break;
            }
        }
    }
    return ret;
}
string f_to_s(string num) {
    for (int i=0; i<num.length(); i++) {
        num[i] = to[num[i] - '0'];
    }
    return num;
}

string add(string num1, string num2)
{
    num1 = s_to_f(num1);
    num2 = s_to_f(num2);
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    int carry = 0;
    string ret = _add(num1, num2, carry);
    ret = f_to_s(ret);
    reverse(ret.begin(), ret.end());
    return ret;
}
string rshift(const string &num2) {
    return "V" + num2.substr(0, num2.length()-1);
}
string lshift(const string &num2) {
    return num2 + "V";
} 

string op(const string &num1, const string &num2, char o) {
    switch (o) {
    case 'A':
        return add(num1, num2);
    case 'R':
        return rshift(num2);
    case 'L':
        return lshift(num2);
    case 'N':
        return num2;
    }
    return "impossible to get here";
}

bool gao()
{
    string num1 = line[0], num2 = line[1];
    for (int i=2; i<=4; i++) {
        num2 = op(num1, num2, line[i][0]);
    }
    while (num2.length() < 8) {
        num2 = "V" + num2;
    }
    return num2 == line[5];
}

int main()
{
    to[0] = 'V'; to[1] = 'U'; to[2] = 'C'; to[3] = 'D';
    puts("COWCULATIONS OUTPUT");
    scanf("%d", &N);
    gets(line[0]);
    while (N--) {
        for (int i=0; i<6; i++) {
            gets(line[i]);
        }
        puts(gao() ? "YES" : "NO");
    }
    puts("END OF OUTPUT");
    return 0;
}