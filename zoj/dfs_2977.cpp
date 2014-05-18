#include "cstdio"
#include "bitset"
#include "cstring"
#include "climits"
using namespace std;

char map[20][20];
char cop[20][20];

int r, c, ans;
int move[5][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}, {0,0}};
int minans;
int old_ans;

inline void flip(int x, int y) {
    if (map[x][y] == 'X') map[x][y] = '.';
    else map[x][y] = 'X';
    //map[x][y] = (map[x][y] == 'X') ? '.' : 'X';
}

inline void change(int x, int y) {
    for (int i=0; i<5; i++) {
        int nx = x + move[i][0];
        int ny = y + move[i][1];
        if (nx>=0 && nx<r && ny>=0 && ny<c) {
            flip(nx, ny);
        }
    }
}

inline void copy_to(char from[][20], char to[][20]) {
    memcpy(to, from, sizeof(map));
    /*
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            to[i][j] = from[i][j];
        }
    }
    */
}

int work() {
    int yes = 1;
    old_ans = ans;
    copy_to(map, cop);
    for (int i=1; i<r; i++) {
        for (int j=0; j<c; j++) {
            if (map[i-1][j] == 'X') {
                change(i, j);
                ans++;
                if (ans > minans) goto done;
            }
        }
    }
    
    for (int j=0; j<c; j++) {
        if (map[r-1][j] == 'X') {
            yes = 0;
            break;
        }
    } 
done:
    copy_to(cop, map);
    return yes;
}

void dfs(int y) {
    if (y == c) {
        if (work()) {
            minans = min(minans, ans);
        }
        ans = old_ans;
        return;
    }


    dfs(y+1);
    change(0, y);
    ans++;
    dfs(y+1);
    ans--;
    change(0, y);

    return;
}

int main(int argc, char const *argv[])
{
    while (scanf("%d%d", &r, &c), r) {
        for (int i=0; i<r; i++) {
            scanf("%s", map[i]);
        }
        ans = 0;
        minans = INT_MAX;
        dfs(0);
        if (minans == INT_MAX) {
            printf("Damaged billboard.\n"); 
        }
        else {
            printf("You have to tap %d tiles.\n",minans);
        }
    }
    return 0;
}