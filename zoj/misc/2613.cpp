#include "cstdio"
#include "map"
#include "string"
#include "vector"
using namespace std;

int U, M;
char name[32];
int price;

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    for (int ci=1; ci<=T; ci++) {
        scanf("%d%d", &U, &M);
        map<int, vector<string> > miv;
        for (int i=0; i<M; i++) {
            scanf("%s%d", name, &price);
            miv[price].push_back(name);
        }

        int low_time = 10001;
        int low_price;
        for (map<int, vector<string> >::iterator it=miv.begin(); 
            it != miv.end(); ++it) {
            vector<string> &vs = it->second;
            if (vs.size() < low_time) {
                low_time = vs.size();
                low_price = it->first;
            }
        }
        printf("Case %d:\n", ci);
        printf("The winner is %s.\n", miv[low_price][0].c_str());
        printf("The price is %d.\n", low_price);
        if (ci != T) {
            printf("\n");
        }
    }
    return 0;
}