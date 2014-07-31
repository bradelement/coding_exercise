#include "iostream"
#include "string"
using namespace std;

int find_match_p(const string &s, int idx) {
    int cur = 1;
    for (int i=idx; i<s.length(); i++) {
        if (s[i] == '(') {
            cur++;
        }
        else if (s[i] == ')') {
            cur--;
            if (cur == 0) return i;
        }
    }
}

string gao(string s) {
    int i;
    for (i=0; i<s.length(); i++) {
        if (s[i]>='a' && s[i]<='z') continue;
        break;
    }
    if (i == s.length()) return s;

    if (s[i] == '(') {
        int j = find_match_p(s, i+1);
        string ret = s.substr(0, i) + gao(s.substr(i+1, j-i-1));
        if (j+1 < s.length()) ret += gao(s.substr(j+1));
        return ret;
    }
    else {
        int num = 0;
        int cur = i;
        while (s[cur] >= '0' && s[cur] <= '9') {
            num = num * 10 + s[cur] - '0';
            cur++;
        }
        if (s[cur] == '(') {
            int j = find_match_p(s, cur+1);
            string tmp = gao(s.substr(cur+1, j-cur-1));
            string rep;
            for (int ii=0; ii<num; ii++) rep += tmp;

            string ret = s.substr(0, i) + rep;
            if (j+1 < s.length()) ret += gao(s.substr(j+1));
            return ret;
        }
        else {
            string rep;
            for (int ii=0; ii<num; ii++) rep += s[cur];
            string ret = s.substr(0, i) + rep;
            if (cur+1 < s.length()) ret += gao(s.substr(cur+1));
            return ret;
        }
    }
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    while (n--) {
        string s;
        cin >> s;
        cout << gao(s) << endl;
    }

    return 0;
}