#include "cstdio"
#include "unordered_map"
#include "unordered_set"
#include "vector"
#include "cstring"
#include "string"
using namespace std;

const int MAXN = 60000;
const int MAXLEN = 21;
int n, m, q;

struct hashfun
{
    int operator()(const char *s) const {
        int seed = 13;
        int ret = 0;
        while (*s) {
            ret = ret * seed + (*s++);
        }
        return ret;
    }
};

struct cmpfun
{
    bool operator()(const char *s1, const char *s2) const {
        return strcmp(s1, s2) == 0;
    }
};

char name[MAXN][MAXLEN];
vector<vector<string> > love;
int rel[MAXN];
char tmpname[MAXLEN];
unordered_map<const char *, int, hashfun, cmpfun> id;
unordered_set<long long> sp;

inline long long shash(long long a, int b) {
    return a * MAXN + b;
}


void input() {
    id.clear();
    scanf("%d%d%d", &n, &m, &q);
    love.resize(n+m);
    for (int i=0; i<n+m; i++) {
        scanf("%s%d", name[i], &rel[i]);
        id.insert(make_pair(name[i], i));
        love[i].resize(rel[i]);
        for (int j=0; j<rel[i]; j++) {
            scanf("%s", tmpname);
            love[i][j] = tmpname;
        }
    }

    sp.clear();
    for (int i=0; i<n+m; i++) {
        for (int j=0; j<rel[i]; j++) {
            sp.insert(shash(i, id[love[i][j].c_str()]));
        }
    }
}

vector<int> vi;

void gao(const vector<int> &vi) {
    int cur = vi[0];
    for (int i=1; i<vi.size(); i++) {
        if (sp.count(shash(vi[i], cur)) || !sp.count(shash(cur, vi[i]))) cur = vi[i];
    }

    bool flag = true;
    for (int i=0; i<vi.size(); i++) {
        if (vi[i] == cur) continue;
        if (sp.count(shash(vi[i], cur)) || !sp.count(shash(cur, vi[i]))) {
            flag = false;
            break;
        }
    }

    if (flag) {
        printf("1 %s\n", name[cur]);
    }
    else {
        printf("0\n");
    }
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    int att;
    while (T--) {
        input();
        for (int i=0; i<q; i++) {
            scanf("%d", &att);
            vi.resize(att);
            for (int j=0; j<att; j++) {
                scanf("%s", tmpname);
                vi[j] = id[tmpname];
            }
            gao(vi);
        }
        printf("\n");
    }
    return 0;
}