#include "cstdio"
#include "vector"
#include "algorithm"
using namespace std;

char pattern[5][6];
int N;
vector<vector<int> > vv;
vector<int> vid;

int main(int argc, char const *argv[])
{
    int total_ci = 1;
    while (1) {
        for (int i=0; i<5; i++) {
            gets(pattern[i]);
        }
        scanf("%d", &N);
        if (N == 0) break;

        if (total_ci > 1) printf("\n");
        printf("Game %d\n", total_ci++);
        vv.clear();
        vid.clear();
        for (int ci=1; ci<=N; ci++) {
            int in;
            vector<int> single;
            for (int i=0; i<5; i++) {
                for (int j=0; j<5; j++) {
                    scanf("%d", &in);
                    if (pattern[i][j] == 'X') {
                        single.push_back(in);
                    }
                }
            }
            sort(single.begin(), single.end());

            bool flag = false;
            for (int i=0; i<vv.size(); i++) {
                if (single == vv[i]) {
                    printf("Card %d is equivalent to card %d\n", ci, vid[i]);
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                vv.push_back(single);
                vid.push_back(ci);
            }
        }
        gets(pattern[0]);
    }
    return 0;
}