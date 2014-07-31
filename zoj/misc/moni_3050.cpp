#include "cstdio"
#include "queue"
#include "vector"
#include "set"
#include "map"
#include "string"
#include "cstring"
#include "cmath"
#include "iostream"
using namespace std;

typedef pair<int, int> point;
typedef pair<point, point> edge;

point make_point(int x, int y) {
    if (x > y) swap(x, y);
    return make_pair(x, y);
}
edge make_edge(point a, point b) {
    if (a > b) swap(a, b);
    return make_pair(a, b);
}
point go(point p, char direction) {
    switch(direction) {
    case 'U':
        p.second++;
        break;
    case 'D':
        p.second--;
        break;
    case 'L':
        p.first--;
        break;
    case 'R':
        p.first++;
        break;
    }
    return p;
}

void print_point(const point &p) {
    printf("(%d,%d)", p.first, p.second);
}

void print_edge(const edge &e) {
    printf("(");
    print_point(e.first);
    printf(", ");
    print_point(e.second);
    printf(")\n");
}

void debug(const set<edge> &se) {
    for (auto i=se.begin(); i!=se.end(); ++i) {
        print_edge(*i);
    }
}

int gcd(int a, int b) {
    return b==0 ? a:gcd(b, a%b);
}

int judge(const set<edge> &se) {
    int heng = 0, shu = 0;
    for (auto i=se.begin(); i!=se.end(); ++i) {
        if ((*i).first.second == (*i).second.second) {
            heng++;
        }
        else {
            shu++;
        }
    }

    point left_top = (*(se.begin())).first;
    int g = gcd(heng, shu);
    heng /= g; shu /= g;
    //printf("heng[%d], shu[%d]\n", heng, shu);
    if (heng==1 && shu==2) {
        //0,7
        point n = make_pair(left_top.first, left_top.second+1);
        if (se.count(make_edge(left_top, n))) {
            return 0;
        }
        return 7;
    }
    else if (heng==0 && shu==1) {
        return 1;
    }
    else if (heng==3 && shu==2) {
        //2,3,5
        point n = make_pair(left_top.first, left_top.second+g);
        point nn = make_pair(left_top.first, left_top.second+g-1);

        if (se.count(make_edge(n, nn))) {
            return 2;
        }
        point r = make_pair(n.first+g, n.second);
        point rr = make_pair(r.first, r.second+1);
        if (!se.count(make_edge(r, rr))) {
            return 5;
        }
        return 3;

    }
    else if (heng==1 && shu==3) {
        return 4;
    }
    else if (heng==1 && shu==1) {
        //6,9
        point n = make_pair(left_top.first, left_top.second+g/3);
        point nn = make_pair(left_top.first, left_top.second+g/3-1);
        if (se.count(make_edge(n, nn))) {
            return 6;
        }
        return 9;
    }
    else {
        return 8;
    }
}

int gao(const string &s) {
    set<edge> se;
    point cur = make_point(0, 0);
    bool is_write = true;
    for (int i=0; i<s.length(); i++) {
        if (s[i] == 'u') {
            is_write = false;
        }
        else if (s[i] == 'd') {
            is_write = true;
        }
        else {
            point new_cur = go(cur, s[i]);
            if (is_write) {
                se.insert(make_edge(cur, new_cur));
            }
            cur = new_cur;    
        }
    }

    //debug(se);
    return judge(se);
}

int main(int argc, char const *argv[])
{
    string s;
    while (cin >> s) {
        cout << gao(s) << endl;
    }
    return 0;
}