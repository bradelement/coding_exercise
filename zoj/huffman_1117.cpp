#include "cstdio"
#include "cstring"
#include "cmath"
#include "iostream"
#include "vector"
#include "string"
#include "map"
#include "queue"
using namespace std;

struct node {
    int freq;
    node *left, *right;

    node(): freq(0), left(NULL), right(NULL) {}
};

struct pcmp
{
    bool operator() (const node *a, const node *b) const{
        return a->freq > b->freq;
    }
};



int deal(node *a, int level) {
    if (a->left == NULL && a->right == NULL) {
        return level * a->freq;
    }
    else {
        return deal(a->left, level+1) + deal(a->right, level+1);
    }
}

void gao(const string &s) {
    map<char, int> m;
    for (int i=0; i<s.length(); i++) {
        m[s[i]]++;
    }
    if (m.size() == 1) {
        int len = s.length() * 8;
        printf("%d %d %.1lf\n", len, len/8, 8.0);
        return;
    }

    priority_queue<node *, vector<node *>, pcmp> q;
    for (auto i=m.begin(); i!=m.end(); ++i) {
        node *tmp = new node();
        tmp->freq = i->second;
        q.push(tmp);
    }

    while (!q.empty()) {
        node *a = q.top(); q.pop();
        if (q.empty()) {
            int ans = deal(a, 0);
            int len = s.length() * 8;
            printf("%d %d %.1lf\n", len, ans, len*1.0/ans);
            break;
        }

        node *b = q.top(); q.pop();

        node *n = new node();
        n->freq = a->freq + b->freq;
        n->left = a;
        n->right = b;
        q.push(n);
    }
}

int main(int argc, char const *argv[])
{
    string s;
    while (1) {
        cin >> s;
        if (s == "END") break;

        gao(s);
    }

    return 0;
}