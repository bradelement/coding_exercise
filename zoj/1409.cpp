#include "cstdio"
#include "vector"
#include "algorithm"
#include "climits"
using namespace std;

struct rec {
    int band, price, idx;
    rec(int b, int p, int i): band(b), price(p), idx(i) {}

    bool operator< (const rec &other) const {
        return band > other.band;
    }
};

int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m, b, p;
        scanf("%d", &n);

        vector<rec> vr;
        vector<int> prices(n, INT_MAX);
        for (int i=0; i<n; i++) {
            scanf("%d", &m);
            for (int j=0; j<m; j++) {
                scanf("%d%d", &b, &p);
                vr.push_back(rec(b, p, i));
            }
        }
        sort(vr.begin(), vr.end());

        double ret = 0;
        for (int i=0; i<vr.size(); i++) {
            if (vr[i].price < prices[vr[i].idx]) {
                prices[vr[i].idx] = vr[i].price;
            }

            double sum = 0;
            for (int j=0; j<n; j++) {
                sum += prices[j];
            }
            ret = max(ret, vr[i].band/(sum));
        }
        printf("%.3lf\n", ret);
    }

    return 0;
}