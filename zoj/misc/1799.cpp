#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

char keyword[16];
char ciphertext[128];
char output[128][128];

void gao() {
    int klen = strlen(keyword);
    int clen = strlen(ciphertext);
    int row = clen / klen;

    vector<pair<char, int> > vp;
    for (int i=0; i<klen; i++) {
        vp.push_back(make_pair(keyword[i], i));
    }
    sort(vp.begin(), vp.end());

    for (int i=0; i<klen; i++) {
        for (int j=0; j<row; j++) {
            output[j][vp[i].second] = ciphertext[i*row+j];
        }
    }
    for (int i=0; i<row; i++) {
        for (int j=0; j<klen; j++) {
            putchar(output[i][j]);
        }
    }
    putchar('\n');
}

int main()
{
    while (gets(keyword), strcmp(keyword, "THEEND")) {
        gets(ciphertext);
        gao();
    }
    return 0;
}