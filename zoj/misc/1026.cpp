#include "cstdio"
#include "vector"
#include "algorithm"
using namespace std;

void print(const vector<int> &v) {
    printf("%d", v.size());
    for (int i=0; i<v.size(); i++) {
        printf(" %d", v[v.size()-1-i]);
    }
    printf("\n");
}

void cls(vector<int> &v) {
    while (v.size() && v[v.size()-1] == 0) {
        v.pop_back();
    }
}

vector<int> m_add(const vector<int> &v1, const vector<int> &v2) {
    vector<int> ret(max(v1.size(), v2.size()));
    for (int i=0; i<v1.size(); i++) {
        ret[i] ^= v1[i];
    }
    for (int i=0; i<v2.size(); i++) {
        ret[i] ^= v2[i];
    }
    cls(ret);
    return ret;
}

vector<int> m_single_mul(int n, const vector<int> &v) {
    vector<int> ret(v.size()+n);
    for (int i=0; i<v.size(); i++) {
        ret[n+i] = v[i];
    }
    cls(ret);
    return ret;
}

vector<int> m_mul(const vector<int> &v1, const vector<int> &v2) {
    vector<int> ret(v1.size()+v2.size());

    for (int i=0; i<v1.size(); i++) {
        if (v1[i]) {
            ret = m_add(ret, m_single_mul(i, v2));
        }
    }
    cls(ret);
    return ret;
}

vector<int> m_sub(const vector<int> &v1, const vector<int> &v2) {
    return m_add(v1, v2);
}

bool lt(const vector<int> &v1, const vector<int> &v2) {
    if (v1.size() < v2.size()) {
        return true;
    }
    else if (v1.size() == v2.size()) {
        for (int i=0; i<v1.size(); i++) {
            int deg = v1.size()-1-i;
            if (v1[deg] > v2[deg]) return false;
        }
        return v1 != v2;
    }
    else {
        return false;
    }
}

vector<int> m_div(const vector<int> &v1, const vector<int> &v2) {
    vector<int> ret;
    if (lt(v1, v2)) return ret;

    vector<int> dividend(v1);
    ret.resize(v1.size() - v2.size() + 1);
    while (!lt(dividend, v2)) {
        int dif = dividend.size()-v2.size();
        ret[dif] = 1;
        dividend = m_sub(dividend, m_single_mul(dif, v2));
    }
    cls(ret);
    return ret;
}

vector<int> m_mod(const vector<int> &v1, const vector<int> &v2) {

    return m_sub(v1, m_mul(m_div(v1, v2), v2));
}

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--) {
        vector<int> vi[3];
        for (int i=0, len; i<3; i++) {
            scanf("%d", &len);
            vi[i].resize(len);
            for (int j=0; j<len; j++) {
                scanf("%d", &vi[i][len-1-j]);
            }
        }
        print(m_mod(m_mul(vi[0], vi[1]), vi[2]));
    }
    return 0;
}