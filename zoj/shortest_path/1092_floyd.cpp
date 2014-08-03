#include "cstdio"
#include "string"
#include "map"
#include "iostream"

const int MAXN = 30;
const int inf = 0x3f3f3f3f;
int n, m;
std::map<std::string, int> name;
double dp[MAXN][MAXN];

void input()
{
    name.clear();
    std::string line;
    for (int i=0; i<n; i++) {
        std::cin >> line;
        name[line] = i;
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            dp[i][j] = 0;
        }
    }
    std::cin >> m;
    std::string a, b;
    double rate;
    for (int i=0; i<m; i++) {
        std::cin >> a >> rate >> b;
        dp[name[a]][name[b]] = rate;
    }
}

void floyd()
{
    double tmp;
    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            if (dp[i][k]) {
                for (int j=0; j<n; j++) {
                    if (dp[k][j]) {
                        tmp = dp[i][k] * dp[k][j];
                        if (tmp > dp[i][j]) {
                            dp[i][j] = tmp;
                        }
                    }
                }
            }
        }
    }
}

bool output()
{
    for (int i=0; i<n; i++) {
        if (dp[i][i] > 1) {
            return true;
        }
    }
    return false;
}

int main(int argc, char const *argv[])
{
    int casen = 1;
    while (std::cin >> n, n) {
        input();
        floyd();
        std::cout << "Case " << casen++ << ": " << \
            (output() ? "Yes" : "No") << std::endl; 
    }
    return 0;
}