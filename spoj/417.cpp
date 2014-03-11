#include <cstdio>
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct {
    int a, b, d;
} contract_t;

bool sort_by_d(const contract_t &a, const contract_t &b)
{
    return a.d < b.d;
}

struct sort_by_a {
    bool operator()(const contract_t &a, const contract_t &b) {
        return a.a < b.a;
    }
};

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        int N;
        scanf("%d", &N);
        vector<contract_t> vc(N);
        for (int i=0; i<N; i++) {
            scanf("%d%d%d", &vc[i].a, &vc[i].b, &vc[i].d);
        }

        sort(vc.begin(), vc.end(), sort_by_d);

        double ans = 0;
        int total_time = 0;
        priority_queue<contract_t, vector<contract_t>, sort_by_a> pq;
        for (int i=0; i<N; i++) {
           pq.push(vc[i]);
           total_time += vc[i].b;
           while (total_time > vc[i].d) {
               contract_t top = pq.top();
               pq.pop();
               int diff = total_time - vc[i].d;
               if (top.b > diff) {
                   top.b -= diff;
                   total_time -= diff;
                   ans += diff * 1.0 / top.a;
                   pq.push(top);
               }
               else {
                   total_time -= top.b;
                   ans += top.b * 1.0 / top.a;
               }
           }
        }

        printf("%.2f\n", ans);
    }

    return 0;
}
