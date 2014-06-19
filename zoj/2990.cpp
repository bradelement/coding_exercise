#include "iostream"
#include "string"
#include "cstring"
#include "cstdio"
using namespace std;

const int MAXN = 25;
int matrix[MAXN][MAXN];

int r, c;
int row[MAXN*MAXN], col[MAXN*MAXN];

char ch(int n) {
    if (n == 0) return ' ';
    return n - 1 + 'A';
}

string gao(string line) {
    int cur = 0;
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            matrix[i][j] = line[cur++] - '0';
        }
    }

    int cr = 0, cc = 0;
    int right = c-1, left = 0, up = 0, down = r-1;
    cur = 0;

    while (cur < line.length()) {
        bool flag = true;
        while (cc < right) {
            row[cur] = cr;
            col[cur] = cc;
            cc++;
            cur++;
            flag = false;
        }
        up++;
        while (cr < down) {
            row[cur] = cr;
            col[cur] = cc;
            cr++;
            cur++;
            flag = false;
        }
        right--;
        while (cc > left) {
            row[cur] = cr;
            col[cur] = cc;
            cc--;
            cur++;
            flag = false;
        }
        down--;
        while (cr > up) {
            row[cur] = cr;
            col[cur] = cc;
            cr--;
            cur++;
            flag = false;
        }
        left++;
        if (flag) {
            row[cur] = cr;
            col[cur] = cc;
            break;
        }
    }

    string ret;
    for (int i=0; i<r*c/5; i++) {
        int v = 0;
        for (int j=0; j<5; j++) {
            v = v * 2 + matrix[row[5*i+j]][col[5*i+j]];
        }
        ret += ch(v);
    }

    int t = ret.length() - 1;
    while (t>=0 && ret[t] == ' ') t--;
    return ret.substr(0, t+1);
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    string line;
    for (int casen=1; casen<=n; casen++) {
        cin >> r >> c >> line;
        cout << casen << ' ' << gao(line) << endl;
    }

    return 0;
}