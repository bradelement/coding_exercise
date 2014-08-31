#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

string line;

bool is_slump(string s) {
    if (s.length() < 3) return false;
    if (s[0] != 'D' && s[0] != 'E') return false;

    int i;
    for (i=1; i<s.length(); i++) {
        if (s[i] != 'F') break;
    }
    if (i == 1) return false;

    if (i == s.length()-1) {
        return s[i] == 'G';
    }
    return is_slump(s.substr(i));
}

bool is_slimp(string s) {
    if (s == "AH") return true;
    if (s.length() <= 4) return false;
    if (s[0] != 'A') return false;
    if (s[s.length()-1] != 'C') return false;

    if (s[1] == 'B') {
        return is_slimp(s.substr(2, s.length()-3));
    }
    else {
        return is_slump(s.substr(1, s.length()-2));
    }
}

bool gao()
{
    for (int i=2; i<line.length(); i++) {
        if (is_slimp(line.substr(0, i)) &&
            is_slump(line.substr(i))) {
                return true;
        }
    }
    return false;
}

int main()
{
    cout << "SLURPYS OUTPUT" << endl;
    int N;
    cin >> N;
    while (N--) {
        cin >> line;
        cout << (gao() ? "YES" : "NO") << endl;
    }
    cout << "END OF OUTPUT" << endl;
}