#include "cstdio"
#include "vector"
using namespace std;

struct Rec
{
    int x1, x2, y1, y2;
};
vector<Rec> vc;

inline bool contain(const Rec &a, const Rec &b) {
    return a.x1 >= b.x1 && a.x2 <= b.x2 && a.y1 >= b.y1 && a.y2 <= b.y2;
}

int main(int argc, char const *argv[])
{
    int n;
    while (~scanf("%d", &n)) {
        vc.resize(n);
        for (int i=0; i<n; i++) {
            scanf("%d%d%d%d", &vc[i].x1, &vc[i].x2, &vc[i].y1, &vc[i].y2);
        }
        int ans = 0;
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (i == j) continue;
                if (contain(vc[i], vc[j])) {
                    ans++;
                    break;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
