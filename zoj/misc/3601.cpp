#include "cstdio"
#include "unordered_map"
#include "unordered_set"
#include "vector"
#include "cstring"
#include "string"
using namespace std;

const int MAXN = 60006;
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
int next_id;
char tmpname[MAXLEN];
unordered_map<const char *, int, hashfun, cmpfun> id;
unordered_set<long long> sp;

inline long long shash(long long a, int b) {
    return a * MAXN + b;
}

inline int gen_id(const char *s) {
    unordered_map<const char *, int, hashfun, cmpfun>::iterator it = id.find(s);
    if (it != id.end()) {
        return it->second; 
    }
    id.insert(make_pair(s, next_id));
    return next_id++;
}

void input() {
    id.clear();
    sp.clear();
    next_id = 0;
    scanf("%d%d%d", &n, &m, &q);
    int tot;
    for (int i=0; i<n+m; i++) {
        scanf("%s%d", name[next_id], &tot);
        int sid = gen_id(name[next_id]);
        for (int j=0; j<tot; j++) {
            scanf("%s", name[next_id]);
            int tid = gen_id(name[next_id]);
            sp.insert(shash(sid, tid));
        }
    }
}

int vi[MAXN];

void gao(int vi[], int tot) {
    int cur = vi[0];
    for (int i=1; i<tot; i++) {
        if (sp.count(shash(vi[i], cur)) || !sp.count(shash(cur, vi[i]))) cur = vi[i];
    }

    bool flag = true;
    for (int i=0; i<tot; i++) {
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
            for (int j=0; j<att; j++) {
                scanf("%s", tmpname);
                vi[j] = id[tmpname];
            }
            gao(vi, att);
        }
        printf("\n");
    }
    return 0;
}