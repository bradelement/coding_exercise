#include "cstdio"
#include "cstring"
#include "vector"
#include "queue"
#include "map"
#include "set"
#include "algorithm"
using namespace std;

const int MAXN = 32;
struct State
{
    int up, down, left, right;
    State(int a=0, int b=0, int c=0, int d=0): up(a), down(b), left(c), right(d) {}
};

char pic[MAXN][MAXN];
int h, w;
set<int> g[MAXN];
vector<char> relation[1024];

int id(int i, int j)
{
    return i*w + j;
}

void build_map(char c, const State &state) {
    for (int i=state.up; i<=state.down; i++) {
        relation[id(i, state.left)].push_back(c);
        relation[id(i, state.right)].push_back(c);
    }
    for (int j=state.left+1; j<state.right; j++) {
        relation[id(state.up, j)].push_back(c);
        relation[id(state.down, j)].push_back(c);
    }
}

void build_graph(char c, int i, int j)
{
    vector<char> &vc = relation[id(i, j)];
    for (int i=0; i<vc.size(); i++) {
        if (vc[i] != c) {
            g[vc[i] - 'A'].insert(c - 'A');
        }
    }
}

void _dfs(int cur, int n, vector<int> &path, vector<bool> &vb, vector<int> &du) {
    if (cur == n) {
        for (int i=0; i<path.size(); i++) {
            printf("%c", path[i] + 'A');
        }
        printf("\n");
        return;
    }

    for (int i=0; i<n; i++) {
        if (!vb[i] && du[i] == 0) {
            vb[i] = true;
            for (set<int>::iterator j=g[i].begin(); j!=g[i].end(); ++j) {
                du[*j]--;
            }
            path.push_back(i);
            _dfs(cur+1, n, path, vb, du);
            path.pop_back();
            for (set<int>::iterator j=g[i].begin(); j!=g[i].end(); ++j) {
                du[*j]++;
            }
            vb[i] = false;
        }
    }
}

void dfs(int n) {
    vector<bool> vb(n, false);
    vector<int> du(n);
    for (int i=0; i<n; i++) {
        for (set<int>::iterator j=g[i].begin(); j!=g[i].end(); ++j) {
            du[*j]++;
        }
    }

    vector<int> path;
    _dfs(0, n, path, vb, du);
}

void gao()
{
    gets(pic[0]);
    for (int i=0; i<h; i++) {
        gets(pic[i]);
    }
    for (int i=0; i<1024; i++) relation[i].clear();
    for (int i=0; i<MAXN; i++) g[i].clear();

    map<char, State> mc;
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            if (pic[i][j] == '.') continue;
            if (mc.count(pic[i][j])) {
                State &s = mc[pic[i][j]];
                if (i < s.up)    s.up = i;
                if (i > s.down)  s.down = i;
                if (j < s.left)  s.left = j;
                if (j > s.right) s.right = j;
            }
            else {
                mc.insert(make_pair(pic[i][j], State(i, i, j, j)));
            }
        }
    }

    for (map<char, State>::iterator i=mc.begin(); i!=mc.end(); ++i) {
        build_map(i->first, i->second);
    }

    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            if (pic[i][j] == '.') continue;
            build_graph(pic[i][j], i, j);
        }
    }

    dfs(mc.size());
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d", &h, &w)) {
        gao();
    }
    return 0;
}