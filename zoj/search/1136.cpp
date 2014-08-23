#include "cstdio"
#include "cstring"
#include "queue"
#include "algorithm"
#include "string"
using namespace std;

int N, m;
int digit[10];
bool vis[5000];

struct State
{
    string s;
    int mod;
    State(const string &a, int b): s(a), mod(b) {}
};

string gao()
{
    if (N == 0) return "0";
    
    memset(vis, 0, sizeof(vis));
    queue<State> q;
    for (int i=0; i<m; i++) {
        if (digit[i] == 0) continue;
        int mod = digit[i] % N;
        if (!vis[mod]) {
            vis[mod] = true;
            string t = "0"; t[0] = digit[i] + '0';
            q.push(State(t, mod));
        }
    }

    while (!q.empty()) {
        State cur = q.front(); q.pop();
        if (cur.mod == 0) {
            return cur.s;
        }
        for (int i=0; i<m; i++) {
            int mod = (cur.mod * 10 + digit[i]) % N;
            if (!vis[mod]) {
                vis[mod] = true;
                string t = "0"; t[0] = digit[i] + '0';
                string n = cur.s + t;
                q.push(State(n, mod));
            }
        }
    }
    return "0";
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d", &N)) {
        scanf("%d", &m);
        for (int i=0; i<m; i++) {
            scanf("%d", &digit[i]);
        }
        sort(digit, digit+m);
        string ans = gao();
        printf("%s\n", ans.c_str());
    } 
    return 0;
}