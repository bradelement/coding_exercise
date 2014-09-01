#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct Record {
    int id, A, SH, CH, R;
};
Record rec[100];
int rec_num;
int id, A, SH, CH, k;
char line[128];

void input() {
    rec_num = 0;
    while (strcmp(line, "")) {
        sscanf(line, "%d%d%d%d%d", &rec[rec_num].id, &rec[rec_num].A, \
            &rec[rec_num].SH, &rec[rec_num].CH, &rec[rec_num].R);
        rec_num++;
        gets(line);
    }
}

int dis(int n) {
    return abs(A-rec[n].A) + abs(SH-rec[n].SH) + abs(CH-rec[n].CH);
}

void _gao() {
    vector<pair<int, int> > vp;
    for (int i=0; i<rec_num; i++) {
        vp.push_back(make_pair(dis(i), i));
    }
    sort(vp.begin(), vp.end());
    int res[2] = {0, 0};
    for (int i=0; i<k; i++) {
        ++res[rec[vp[i].second].R];
    }
    printf("%d %d\n", id, res[0]>res[1] ? 0 : 1);
}

bool gao() {
    while (1) {
        if (!gets(line)) {
            return false;
        }
        if (strstr(line, " ")) {
            return true;
        }
        k = atoi(line);

        gets(line);
        while (strcmp(line, "")) {
            sscanf(line, "%d%d%d%d", &id, &A, &SH, &CH);
            _gao();
            if (!gets(line)) break;
        }
    }
}

int main()
{
    gets(line);
    while (1) {
        input();
        if (!gao()) break;
    }
    return 0;
}