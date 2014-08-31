#include "cstdio"
#include "cstring"
#include "iostream"
#include "vector"
#include "string"
#include "queue"
using namespace std;

struct Node
{
    string num;
    bool valid;
    Node *left, *right;

    Node(string a="r", bool b=false): num(a), valid(b), left(NULL), right(NULL) {}
};
bool is_ok;

Node *build_tree(const vector<string> &vs) {
    Node *root = new Node();

    for (int i=0; i<vs.size(); i++) {
        const string &curs = vs[i];
        int idx = curs.find(',');
        string num = curs.substr(1, idx-1);
        string path = curs.substr(idx+1, curs.length()-idx-2);

        Node *cur = root;
        for (int j=0; j<path.length(); j++) {
            if (path[j] == 'L') {
                if (cur->left == NULL) {
                    cur->left = new Node();
                }
                cur = cur->left;
            }
            else {
                if (cur->right == NULL) {
                    cur->right = new Node();
                }
                cur = cur->right;
            }
        }
        if (cur->valid) {
            is_ok = false;
        }
        cur->num = num;
        cur->valid = true;
    }

    return root;
}

void level_order_traversal(Node *root, vector<string> &vs) {
    queue<Node *> Q;
    Q.push(root);
    while (!Q.empty()) {
        Node *cur = Q.front(); Q.pop();
        if (cur == NULL) continue;
        if (!cur->valid) {
            is_ok = false;
        }
        vs.push_back(cur->num);
        Q.push(cur->left);
        Q.push(cur->right);
    }
}

int main(int argc, char const *argv[])
{
    string seg;
    while (1) {
        if (!(cin >> seg)) break;
        vector<string> in;
        while (seg != "()") {
            in.push_back(seg);
            cin >> seg;
        }
        is_ok = true;
        Node *root = build_tree(in);

        vector<string> vs;
        level_order_traversal(root, vs);
        if (is_ok) {
            for (int i=0; i<vs.size(); i++) {
                if (i) cout << ' ';
                cout << vs[i];
            }
            cout << endl;
        }
        else {
            cout << "not complete" << endl;
        }

    }
    return 0;
}