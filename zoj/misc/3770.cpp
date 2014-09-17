#include "cstdio"
#include "cstring"
#include "algorithm"

struct Member
{
    int id, score, idx;
    char t[12];
    bool operator< (const Member &other) const {
        return score < other.score ||
            (score == other.score && (strcmp(t, other.t) > 0 || (strcmp(t, other.t) == 0 && id > other.id)));
    }
};

const int MAXN = 2048;
Member people[MAXN];
int rank[MAXN];

int get_num(int sum, int level) {
    switch (level) {
    case 6:
        return sum * 0.03;
    case 5:
        return sum * 0.07;
    case 4:
        return sum * 0.2;
    case 3:
        return sum * 0.3;
    default:
        return sum;
    }
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);

        int sum = 0;
        for (int i=0; i<N; i++) {
            scanf("%d%s%d", &people[i].id, people[i].t, &people[i].score);
            if (people[i].score > 0) sum++;
            people[i].idx = i;
        }
        std::sort(people, people+N);

        int cur = N-1;
        int level = 7;
        int num = 0;
        while (cur >= 0 && people[cur].score > 0) {
            while (num == 0) {
                level--;
                num = get_num(sum, level);
            }
            rank[people[cur].idx] = level;
            num--;
            cur--;
        }
        while (cur >= 0) {
            rank[people[cur].idx] = 1;
            cur--;
        }

        for (int i=0; i<N; i++) {
            printf("LV%d\n", rank[i]);
        }
    }
    return 0;
}