#include "cstdio"
#include "map"
#include "string"
#include "set"
#include "iostream"
#include "vector"
using namespace std;

void gao(map<string, vector<pair<string, int> > > &m, string father, int age, \
    map<int, set<string> > &info) {

        for (int i=0; i<m[father].size(); i++) {
            string name = (m[father][i]).first;
            int sage = age - (m[father][i]).second;
            info[sage].insert(name);
            gao(m, name, sage, info);
        }
}

int main(int argc, char const *argv[])
{
    int casen;
    cin >> casen;
    for (int ci=1; ci<=casen; ci++) {
        int ln;
        cin >> ln;
        string father, son;
        double age;
        map<string, vector<pair<string, int> > > m;
        while (ln--) {
            cin >> father >> son >> age;
            m[father].push_back(make_pair(son, age));
        }

        map<int, set<string> > info;
        gao(m, "Ted", 100, info);

        cout << "DATASET " << ci << endl;
        for (map<int, set<string> >::reverse_iterator i=info.rbegin(); i!=info.rend(); ++i) {
            for (set<string>::iterator j=(i->second).begin(); j!=(i->second).end(); ++j) {
                cout << *j << ' ' << i->first << endl;
            }
        }
    }

    return 0;
}