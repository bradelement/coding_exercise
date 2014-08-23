#include "cstdio"
#include "cstring"
#include "string"
#include "queue"
using namespace std;

const int MAXN = 1000;
bool vis[1<<10][MAXN];

struct State
{
    short int cur_digit, mod, mask;
    int pre;
    State(int a=0, int b=0, int c=0, int d=0): cur_digit(a), mod(b), mask(c), pre(d) {}
};

State s[(1<<10) * MAXN];
int qcur;

inline int cal_count(int n) {
    int ans = 0;
    while (n) {
        ans++;
        n &= n-1;
    }
    return ans;
}

string p(int idx) {
    string ret;
    do {
        ret.insert(0, 1, '0'+s[idx].cur_digit);
        idx = s[idx].pre;
    } while (idx != -1);
    return ret;
}

string gao(int n, int m)
{
    memset(vis, 0, sizeof(vis));
    qcur = 0;
    queue<int> q;

    for (int i=1; i<=9; i++) {
        int mod = i % n;
        int mask = 1<<i;
        if (!vis[mask][mod]) {
            q.push(qcur);
            vis[mask][mod] = true;
            State &cur = s[qcur];
            cur.cur_digit = i;
            cur.mod = mod;
            cur.mask = mask;
            cur.pre = -1;
            qcur++;
        }
    }

    while (!q.empty()) {
        int idx = q.front(); q.pop();
        State &cur = s[idx];
        if (cur.mod == 0 && cal_count(cur.mask) == m) {
            return p(idx);
        }
        for (int i=0; i<=9; i++) {          
            int mod = (cur.mod*10 + i);
            while (mod >= n) mod -= n;

            int mask = cur.mask | (1<<i);
            if (!vis[mask][mod]) {
                q.push(qcur);
                vis[mask][mod] = true;
                State &ne = s[qcur];
                ne.cur_digit = i;
                ne.mod = mod;
                ne.mask = mask;
                ne.pre = idx;
                qcur++;
            }
        }
    }
    return "Impossible";
}

string divide(const string &s, int n) {
    bool flag = false;
    string ret;
    int mod = 0;
    for (int i=0; i<s.length(); i++) {
        mod = mod * 10 + s[i] - '0';
        if (mod >= n) {
            flag = true;
            ret += '0' + mod / n;
            mod %= n;
        }
        else if (flag) {
            ret += '0';
        }
    }
    return ret;
}

int main(int argc, char const *argv[])
{
    int t, n, m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        string ans = gao(n, m);
        if (ans[0] == 'I') {
            printf("%s\n", ans.c_str());    
        }
        else {
            string q = divide(ans, n);
            printf("%s=%d*%s\n", ans.c_str(), n, q.c_str());
        }
    }
    return 0;
}