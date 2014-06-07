#include "cstdio"
#include "iostream"
#include "string"
#include "cstdlib"
#include "cstring"
#include "vector"
#include "algorithm"
using namespace std;

vector<int> statement_list();

vector<int> loop() {
    string token;
    cin >> token;

    if (token == "n") {
        vector<int> r = statement_list();
        vector<int> ret(r.size()+1);
        for (int i=0; i<r.size(); i++) {
            ret[i+1] = r[i];
        }

        return ret;
    }
    else {
        vector<int> r = statement_list();
        int n = atoi(token.c_str());
        for (int i=0; i<r.size(); i++) {
            r[i] *= n;
        }

        return r;
    }

}

vector<int> op() {
    string token;
    cin >> token;

    vector<int> ret(1);
    ret[0] = atoi(token.c_str());

    return ret;
}

vector<int> statement(string token) {
    vector<int> ret;

    if (token == "LOOP") {
        ret = loop();
    }
    else {
        ret = op();
    }

    return ret;
}

vector<int> statement_list() {
    vector<int> ret(1);

    string token;
    while (1) {
        cin >> token;
        if (token == "END") break;

        vector<int> stat = statement(token);
        if (ret.size() < stat.size()) {
            int diff = stat.size()-ret.size();
            for (unsigned int i=0; i<diff; i++) {
                ret.push_back(0);
            }
        }
        for (int i=0; i<stat.size(); i++) {
            ret[i] += stat[i];
        }
    }

    return ret;
}

vector<int> parse() {
    string line;
    cin >> line; //skip begin

    vector<int> ret = statement_list();
    return ret;
}

string itoa(int n) {
    string ret;

    do {
        ret += '0' + n % 10;
        n /= 10;
    } while (n);

    reverse(ret.begin(), ret.end());
    return ret;
}

string display(const vector<int> &v) {
    vector<string> arr;
    for (unsigned int i=v.size()-1; i>=1; i--) {
        if (v[i]) {
            string ret;
            if (v[i] > 1) {
                ret += itoa(v[i]);
                ret += "*";
            }
            ret += "n";

            if (i>1) {
                ret += "^";
                ret += itoa(i);
            }
            arr.push_back(ret);
        }
    }
    if (v[0]) arr.push_back(itoa(v[0]));
    if (arr.size() == 0) arr.push_back("0");

    string final;
    for (unsigned int i=0; i<arr.size()-1; i++) {
        final += arr[i];
        final += "+";
    }
    final += arr[arr.size()-1];
    return final;
}

int main(int argc, char const *argv[])
{
    int casen;
    cin >> casen;

    for (int c=1; c<=casen; c++) {
        vector<int> ret = parse();

        cout << "Program #" << c << endl;
        cout << "Runtime = " << display(ret) << endl;
        cout << endl;
    }

    return 0;
}