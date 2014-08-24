#include "cstdio"
#include "unordered_map"
#include "vector"
#include "algorithm"
using namespace std;

int N, K;
unordered_map<int, vector<int> > m;

int max_range_sum(const vector<int> &v) {
    int start = 0, end = 0;
    int cur = K, cur_sum = v[0], sum = v[0];
    while (end < v.size()-1) {
        if (cur + v[end+1] >= 0) {
            cur_sum += v[end+2];
            cur += v[end+1];
            end += 2;
            if (cur_sum > sum) sum = cur_sum;
        }
        else {
            cur_sum -= v[start];
            cur -= v[start+1];
            start += 2;
        }
    }

    return sum;
}

int _gao(const vector<int> &v) {
    vector<int> a;
    //a.reserve(v.size() * 2);
    for (int i=0; i<v.size(); i++) {
        if (i == 0) {
            a.push_back(1);
            continue;
        }

        if (v[i] == v[i-1]+1) {
            a[a.size()-1]++;
        }
        else {
            a.push_back(-(v[i] - v[i-1] - 1));
            a.push_back(1);
        }
    }

    return max_range_sum(a);
}

int gao()
{
    m.clear();
    for (int i=0, tmp; i<N; i++) {
        scanf("%d", &tmp);
        m[tmp].push_back(i);
    }

    int ans = -1;
    for (unordered_map<int, vector<int> >::iterator i=m.begin(); i!=m.end(); ++i) {
        ans = max(ans, _gao(i->second));
    }
    return ans;
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d", &N, &K)) {
        printf("%d\n", gao());
    }
    return 0;
}