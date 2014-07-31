#include "iostream"
#include "string"
#include "cstring"
#include "cstdio"
using namespace std;

const int MAXN = 25;
int matrix[MAXN][MAXN];

int r, c;
int row[MAXN*MAXN], col[MAXN*MAXN];

int v(char c) {
    if (c == ' ')  return 0;
    return c-'A'+1;
}

void gao(string line) {
    memset(matrix, 0, sizeof(matrix));
    int cr = 0, cc = 0;
    int right = c-1, left = 0, up = 0, down = r-1;
    int cur = 0;

    while (cur < line.length() * 5) {
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

    int arr[5];
    for (int i=0; i<line.length(); i++) {
        int value = v(line[i]);
        memset(arr, 0, sizeof(arr));
        int idx = 4;
        while (value) {
            arr[idx--] = value % 2;
            value /= 2;
        }

        for (int j=0; j<5; j++) {
            matrix[row[5*i+j]][col[5*i+j]] = arr[j];
        }
    }

    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            cout << matrix[i][j];
        }
    }
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    for (int casen=1; casen<=n; casen++) {
        cin >> r >> c;
        cin.get();

        string line;
        getline(cin, line);

        cout << casen << ' ';
        gao(line);
        cout << endl;
    }

    return 0;
}