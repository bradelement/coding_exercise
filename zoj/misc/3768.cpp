#include "cstdio"
#include "vector"
#include "algorithm"
using namespace std;

//任意自然数是最多三个三角形数的和
//高斯发现了这个规律。他在1796年7月10日在日记中写道：EYPHKA! num = Δ + Δ + Δ

const int lim = 123456789;
vector<int> num;

bool gao(int n, vector<int> &ans)
{
    int target;
    vector<int>::iterator it = lower_bound(num.begin()+1, num.end(), n);
    if (*it == n) {
        ans.push_back(it - num.begin());
        return true;
    }
    for (int i=1; i<num.size(); i++) {
        target = n - num[i];
        if (target < 0) break;
        it = lower_bound(num.begin()+1, num.end(), target);
        if (*it == target) {
            ans.push_back(i);
            ans.push_back(it - num.begin());
            return true;
        }
    }

    for (int i=1; i<num.size(); i++) {
        for (int j=i; j<num.size(); j++) {
            target = n - num[i] - num[j];
            if (target < 0) continue;
            it = lower_bound(num.begin()+1, num.end(), target);
            if (*it == target) {
                ans.push_back(i);
                ans.push_back(j);
                ans.push_back(it - num.begin());
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char const *argv[])
{
    int t, n;
    for (int i=0; ;i++) {
        t = (i+1) * i / 2;
        if (t > lim) break;
        num.push_back(t);
    }

    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        vector<int> ans;
        gao(n, ans);
        for (int i=0; i<ans.size(); i++) {
            if (i) printf(" ");
            printf("%d", ans[i]);
        }
        printf("\n");
    }

    return 0;
}