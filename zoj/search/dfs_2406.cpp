#include "cstdio"
#include "iostream"
#include "cstring"
#include "cmath"
#include "string"
#include "vector"
#include "set"
#include "map"
#include "algorithm"
#include "climits"
using namespace std;

const int MAXTOWN = 21;
int NV, NR, SV, DV, MAXDIST;
int routemap[MAXTOWN][MAXTOWN];
int used[MAXTOWN];
map<int, vector<vector<int> > > ans;

void dfs(int from, int dist, vector<int> &route) {
    if (dist > MAXDIST) return;
    if (from == DV && dist <= MAXDIST) {
        route.push_back(from);
        ans[dist].push_back(route);
        route.pop_back();
        return;
    }
    for (int i=1; i<=NV; i++) {
        if (!used[i] && routemap[from][i] > 0) {
            int tmp = routemap[from][i];
            routemap[from][i] = routemap[i][from] = -1;
            route.push_back(from);
            used[i] = 1; 
            dfs(i, dist+tmp, route);
            used[i] = 0;
            route.pop_back();
            routemap[from][i] = routemap[i][from] = tmp;
        }
    }
}

int main(int argc, char const *argv[])
{
    int a, b, c;
    int casen = 1;
    bool first = true;
    while (scanf("%d", &NV), NV!=-1) {
        if (first) first = false;
        else {
            printf("\n");
        }

        scanf("%d", &NR);
        memset(routemap, -1, sizeof(routemap));
        memset(used, 0, sizeof(used));
        for (int i=0; i<NR; i++) {
            scanf("%d%d%d", &a, &b, &c);
            routemap[a][b] = routemap[b][a] = c;
        }

        scanf("%d%d", &SV, &DV);
        scanf("%d", &MAXDIST);
        ans.clear();
        vector<int> route;
        used[SV] = 1;
        dfs(SV, 0, route);

        printf("Case %d:\n", casen++);
        for (map<int, vector<vector<int> > >::iterator i=ans.begin(); \
            i!=ans.end(); ++i) {
            int k = i->first;
            vector<vector<int> > &v = i->second;
            sort(v.begin(), v.end());
            for (int ii=0; ii<v.size(); ii++) {
                printf(" %d:", k);
                for (int jj=0; jj<v[ii].size(); jj++) {
                    printf(" %d", v[ii][jj]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}