#include "iostream"
#include "string"
#include "cstdio"
using namespace std;

int cal_common(const string &a, const string &b) {
    int ret = 0;
    for (int i=0; i<a.length(); i++) {
        if (a[i] == b[i]) ret++;
    }
    return ret;
}

int gcd(int a, int b) {
    return b==0 ? a : gcd(b, a%b);
}

string fac(int a, int b) {
    if (a == 0) return "0";
    else if (a == b) return "1";

    int g = gcd(a, b);
    char line[32];
    sprintf(line, "%d/%d", a/g, b/g);
    return line;
}

void gao(string a, string b) {
    printf("appx(%s,%s) = ", a.c_str(), b.c_str());
    int sum = a.length() + b.length();
    b.insert(0, a.size()-1, ' ');
    b.append(a.size()-1, ' ');
    int common = -1;
    for (int i=0, tmp; i+a.length()<=b.length(); i++) {
        tmp = cal_common(a, b.substr(i, a.length()));
        if (tmp > common) common = tmp;
    }
    printf("%s\n", fac(common*2, sum).c_str());

}

int main(int argc, char const *argv[])
{
    string a, b;
    while (cin >> a, a != "-1") {
        cin >> b;
        gao(a, b);
    }
    return 0;
}