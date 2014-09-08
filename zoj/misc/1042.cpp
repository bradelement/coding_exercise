#include "cstdio"
#include "cstring"
#include "vector"

int k[3];
char line[100];
char ans[100];

int group(char c) {
    if (c >= 'a' && c <= 'i') return 0;
    else if (c >= 'j' && c <= 'r') return 1;
    else return 2;
}

void gao() {
    int len = strlen(line);
    std::vector<int> pos[3];
    for (int i=0; i<len; i++) {
        pos[group(line[i])].push_back(i);
    }

    for (int i=0; i<3; i++) {
        for (int j=0; j<pos[i].size(); j++) {
            ans[pos[i][(j+k[i]) % pos[i].size()]] = line[pos[i][j]];
        }
    }
    ans[len] = 0;
    puts(ans);
}

int main(int argc, char const *argv[])
{
    while (scanf("%d%d%d", &k[0], &k[1], &k[2]), k[0]+k[1]+k[2]) {
        gets(line);
        gets(line);
        gao();
    }
    return 0;
}