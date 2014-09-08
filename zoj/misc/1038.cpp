#include "cstdio"
#include "iostream"
#include "string"
#include "map"
#include "vector"
#include "algorithm"
using namespace std;

map<string, int> dic;
map<string, vector<pair<string, int> > > mapping;

char _trans(char c) {
    if (c >= 'a' && c <= 'c') {
        return '2';
    }
    else if (c >= 'd' && c <= 'f') {
        return '3';
    }
    else if (c >= 'g' && c <= 'i') {
        return '4';
    }
    else if (c >= 'j' && c <= 'l') {
        return '5';
    }
    else if (c >= 'm' && c <= 'o') {
        return '6';
    }
    else if (c >= 'p' && c <= 's') {
        return '7';
    }
    else if (c >= 't' && c <= 'v') {
        return '8';
    }
    else if (c >= 'w' && c <= 'z') {
        return '9';
    }
    else {
        return '0';
    }
}

string trans(const string &s) {
    string ret;
    for (int i=0; i<s.length(); i++) {
        ret += _trans(s[i]);
    }
    return ret;
}

bool cmp(const pair<string, int> &a, const pair<string, int> &b) {
    return a.second > b.second || (a.second == b.second && a.first < b.first);
}

void input() {
    dic.clear();
    int w;
    cin >> w;
    string s;
    int p;
    for (int i=0; i<w; i++) {
        cin >> s >> p;
        for (int j=1; j<=s.length(); j++) {
            dic[s.substr(0, j)] += p;
        }
    }
    mapping.clear();
    for (map<string, int>::iterator it=dic.begin(); it!=dic.end(); ++it) {
        string k = trans(it->first);
        mapping[k].push_back(make_pair(it->first, it->second));
    }
    for (map<string, vector<pair<string, int> > >::iterator it=mapping.begin(); it!=mapping.end(); ++it) {
        vector<pair<string, int> > &vp = it->second;
        sort(vp.begin(), vp.end(), cmp);
    }
}

void gao(const string &stroke) {
    for (int i=1; i<stroke.length(); i++) {
        string k = stroke.substr(0, i);
        map<string, vector<pair<string, int> > >::iterator it = mapping.find(k);
        if (it == mapping.end()) {
            puts("MANUALLY");
        }
        else {
            vector<pair<string, int> > &vp = it->second;
            puts(vp[0].first.c_str());
        }
    }
    puts("");
}

int main(int argc, char const *argv[])
{
    int T, m;
    cin >> T;
    for (int ci=1; ci<=T; ci++) {
        input();
        cin >> m;
        string stroke;
        printf("Scenario #%d:\n", ci);
        for (int i=0; i<m; i++) {
            cin >> stroke;
            gao(stroke);
        }
        puts("");
    }
    return 0;
}