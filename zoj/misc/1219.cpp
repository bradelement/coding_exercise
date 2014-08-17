#include "cstdio"
#include "cstring"
#include "vector"
using namespace std;

char line[128];

bool check(const vector<vector<pair<int, int> > > &v, int mask)
{
    for (int i=0; i<v.size(); i++) {
        bool flag = false;
        for (int j=0; j<v[i].size(); j++) {
            if ((mask & (1<<v[i][j].first)) == (v[i][j].second << v[i][j].first)) {
                flag = true;
                break;
            }
        }
        if (!flag) return false;
    }
    return true;
}

void output(int n)
{
    printf("Toppings: ");
    int cur = 0;
    while (n) {
        if (n & 1) {
            putchar('A'+cur);
        }
        n >>= 1;
        cur++;
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    while (1) {
        if (!gets(line)) break;
        vector<vector<pair<int, int> > > v;

        while (strcmp(line, ".")) {
            vector<pair<int, int> > tmp;
            for (int i=0; line[i]!=';'; i+=2) {
                int used = line[i] == '+' ? 1 : 0;
                int idx  = line[i+1] - 'A';
                tmp.push_back(make_pair(idx, used));
            }
            v.push_back(tmp);
            gets(line);
        }

        bool flag = false;
        for (int i=0; i<(1<<16); i++) {
            if (check(v, i)) {
                output(i);
                flag = true;
                break;
            }
        }
        if (!flag) {
            puts("No pizza can satisfy these requests.");
        }
    }
    return 0;
}