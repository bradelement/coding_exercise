#include "cstdio"
#include "cstring"
#include "cctype"
#include "list"
#include "vector"
using namespace std;

const int MAXN = 51;
list<int> edges[MAXN];
char line[1024];
int maxn;

int get_num(int cur) {
    int ret = 0;
    while (isdigit(line[cur])) {
        ret = ret * 10 + line[cur] - '0';
        cur++;
    }
    return ret;
}

int parse(int start) {
    int root = get_num(start+1);
    if (root > maxn) {
        maxn = root;
    }
    int cur = start+1, para = 1;
    while (1) {
        if (line[cur] == '(') {
            para++;
            if (para == 2) {
                int child = parse(cur);
                edges[root].push_back(child);
                edges[child].push_back(root);
            }
        }
        else if (line[cur] == ')') {
            para--;
            if (para == 0) {
                return root;
            }
        }
        cur++;
    }
}

void gao() {
    for (int i=0; i<MAXN; i++) {
        edges[i].clear();
    }
    maxn = -1;
    parse(0);

    vector<int> ans;
    vector<int> vis(maxn+1);
    for (int i=0; i<maxn-1; i++) {
        for (int j=1; j<=maxn; j++) {
            if (!vis[j] && edges[j].size() == 1) {
                vis[j] = 1;
                int fa = edges[j].front();
                edges[fa].remove(j);
                ans.push_back(fa);
                break;
            }
        }
    }

    for (int i=0; i<ans.size(); i++) {
        if (i) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    while (gets(line)) {
        gao();
    }
    return 0;
}