#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
using namespace std;

struct Register {
    double value[4];
    Register(double a=0.0, double b=0.0, double c=0.0, double d=0.0) {
        value[0] = a;
        value[1] = b;
        value[2] = c;
        value[3] = d;
    }
    Register(const Register &other) {
        for (int i=0; i<4; i++) {
            value[i] = other.value[i];
        }
    }
    Register &operator=(const Register &other) {
        for (int i=0; i<4; i++) {
            value[i] = other.value[i];
        }
        return *this;
    } 
};
Register operator+(const Register &a, const Register &b) {
    Register ret;
    for (int i=0; i<4; i++) {
        ret.value[i] = a.value[i] + b.value[i];
    }
    return ret;
}
Register operator-(const Register &a, const Register &b) {
    Register ret;
    for (int i=0; i<4; i++) {
        ret.value[i] = a.value[i] - b.value[i];
    }
    return ret;
}
Register operator*(const Register &a, const Register &b) {
    Register ret;
    for (int i=0; i<4; i++) {
        ret.value[i] = a.value[i] * b.value[i];
    }
    return ret;
}

map<string, Register> gmap;
map<char, int> vmap;
typedef void (*f)(const string &);
map<string, f> fmap;
char dst[32], src0[32], src1[32], src2[32];
double v1, v2, v3, v4;
int slots_count;

void register_print(const Register &r) {
    for (int i=0; i<4; i++) {
        printf("%.3lf ", r.value[i]);
    }
}

Register register_get(const string &name) {
    int idx = name.find('.');
    if (idx == string::npos) {
        return gmap[name];
    }

    Register ret;
    Register tmp = gmap[name.substr(0, idx)];
    string remain = name.substr(idx+1);
    for (int i=0; i<remain.length(); i++) {
        ret.value[i] = tmp.value[vmap[remain[i]]];
    }

    return ret;
}
void register_set(const string &name, Register r) {
    int idx = name.find('.');
    if (idx == string::npos) {
        gmap[name] = r;
        return;
    }

    Register &tmp = gmap[name.substr(0, idx)];
    string remain = name.substr(idx+1);
    for (int i=0; i<remain.length(); i++) {
        tmp.value[vmap[remain[i]]] = r.value[i];
    }
}

void init() {
    gmap.clear();
    slots_count = 0;
}

void madd(const string &line) {
    slots_count += 1;
    sscanf(line.c_str(), "%*s %[^,], %[^,], %[^;];", dst, src0, src1);
    Register s0 = register_get(src0);
    Register s1 = register_get(src1);
    register_set(dst, s0+s1);
}
void mdef(const string &line) {
    sscanf(line.c_str(), "%*s %[^,], %lf, %lf, %lf, %lf;", dst, &v1, &v2, &v3, &v4);
    gmap[dst] = Register(v1, v2, v3, v4);
}
void mdp3(const string &line) {
    slots_count += 1;
    sscanf(line.c_str(), "%*s %[^,], %[^,], %[^;];", dst, src0, src1);
    Register s0 = register_get(src0);
    Register s1 = register_get(src1);

    double v = 0.0;
    for (int i=0; i<3; i++) {
        v += s0.value[i] * s1.value[i];
    }
    register_set(dst, Register(v, v, v, v));
}
void mfrc(const string &line) {
    slots_count += 1;
    sscanf(line.c_str(), "%*s %[^,], %[^;];", dst, src0);
    Register s0 = register_get(src0);
    for (int i=0; i<4; i++) {
        s0.value[i] -= floor(s0.value[i]);
    }
    register_set(dst, s0);
}
void mmad(const string &line) {
    slots_count += 2;
    sscanf(line.c_str(), "%*s %[^,], %[^,], %[^,], %[^;];", dst, src0, src1, src2);
    Register s0 = register_get(src0);
    Register s1 = register_get(src1);
    Register s2 = register_get(src2);
    register_set(dst, (s0 * s1) + s2);
}
void mmax(const string &line) {
    slots_count += 1;
    sscanf(line.c_str(), "%*s %[^,], %[^,], %[^;];", dst, src0, src1);
    Register s0 = register_get(src0);
    Register s1 = register_get(src1);
    Register mr;
    for (int i=0; i<4; i++) {
        mr.value[i] = max(s0.value[i], s1.value[i]);
    }
    register_set(dst, mr);
}
void mmov(const string &line) {
    slots_count += 1;
    sscanf(line.c_str(), "%*s %[^,], %[^;];", dst, src0);
    Register s0 = register_get(src0);
    register_set(dst, s0);
}
void mmul(const string &line) {
    slots_count += 1;
    sscanf(line.c_str(), "%*s %[^,], %[^,], %[^;];", dst, src0, src1);
    Register s0 = register_get(src0);
    Register s1 = register_get(src1);
    register_set(dst, s0*s1);
}

void mexec(const string &line) {
    string name = line.substr(0, 3);
    fmap[name](line);
}

void gao(const vector<string> &vs) {
    init();
    for (int i=0; i<vs.size(); i++) {
        mexec(vs[i]);
    }
    register_print(gmap["oC0"]);
    printf("%d\n", slots_count);
}

void global_init() {
    fmap["add"] = madd;
    fmap["def"] = mdef;
    fmap["dp3"] = mdp3;
    fmap["frc"] = mfrc;
    fmap["mad"] = mmad;
    fmap["max"] = mmax;
    fmap["mov"] = mmov;
    fmap["mul"] = mmul;

    vmap['x'] = vmap['r'] = 0;
    vmap['y'] = vmap['g'] = 1;
    vmap['z'] = vmap['b'] = 2;
    vmap['w'] = vmap['a'] = 3;
}

int main()
{
    global_init();
    bool stop = false;
    while (1) {
        string line;
        vector<string> vs;
        while (1) {
            if (!getline(cin, line)) {
                stop = true;
                break;
            }
            if (line == "") break;
            vs.push_back(line);
        }
        if (stop) break;
        gao(vs);   
    }

    return 0;
}