#include "cstdio"
#include "vector"
#include "algorithm"
using namespace std;

struct Course
{
    int s, t, idx;
    bool operator< (const Course &o) const {
        if (t < o.t) return true;
        else if (t == o.t && s < o.s) return true;
        return false;
    }
};

const int MAXN = 100001;
Course course[MAXN];
int N;

void gao()
{
    for (int i=1; i<=N; i++) {
        course[i].idx = i;
        scanf("%d%d", &course[i].s, &course[i].t);
    }
    sort(course+1, course+1+N);

    vector<vector<int> > ans;
    int end_time = -1;
    for (int i=1; i<=N; i++) {
        if (course[i].s >= end_time) {
            end_time = course[i].t;
            vector<int> n;
            n.push_back(course[i].idx);
            ans.push_back(n);
        }
        else {
            ans[ans.size()-1].push_back(course[i].idx);
        }
    }

    printf("%d\n", ans.size());
    for (int i=0; i<ans.size(); i++) {
        for (int j=0; j<ans[i].size(); j++) {
            if (j) printf(" ");
            printf("%d", ans[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d", &N)) {
        gao();
    }
    return 0;
}