#include "cstdio"
#include "cstring"
#include "map"
#include "vector"
#include "stack"

const int MAXN = 32;
char line1[MAXN+1], line2[MAXN+1];
int len1, len2;

void dfs(int i1, int i2, std::vector<char> &output, std::stack<char> &sc) {
    if (i2 == len2) {
        for (int i=0; i<output.size(); i++) {
            printf("%c ", output[i]);
        }
        printf("\n");
        return;
    }
    
    if (i1 < len1) {
        sc.push(line1[i1]);
        output.push_back('i');
        dfs(i1+1, i2, output, sc);
        output.pop_back();
        sc.pop();
    }
    if (!sc.empty()) {
        if (line2[i2] == sc.top()) {
            output.push_back('o');
            sc.pop();
            dfs(i1, i2+1, output, sc);
            sc.push(line2[i2]);
            output.pop_back();
        }
    }
}

void gao() {
    len1 = strlen(line1);
    len2 = strlen(line2);
    if (len1 != len2) return;

    std::map<char, int> m1, m2;
    for (int i=0; i<len1; i++) {
        ++m1[line1[i]];
        ++m2[line2[i]];
    }
    if (m1 != m2) return;

    std::stack<char> sc;
    std::vector<char> vc;
    dfs(0, 0, vc, sc);
}

int main(int argc, char const *argv[])
{
    while (gets(line1), gets(line2)) {
        puts("[");
        gao();
        puts("]");
    }
    return 0;
}