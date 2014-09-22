#include "cstdio"
#include "cstring"
#include "vector"
using namespace std;

char line[32];
int hour, minute, second;
double speed;
vector<pair<int, double> > vp;

int sec() {
    return hour*3600 + minute*60 + second;
}

double cal() {
    if (vp.size() == 0) return 0;

    double ret = 0;
    int curt = sec();
    for (int i=0; i<vp.size()-1; i++) {
        ret += vp[i].second * (vp[i+1].first - vp[i].first);
    }
    ret += vp[vp.size()-1].second * (curt - vp[vp.size()-1].first);
    return ret / 1000;
}

int main(int argc, char const *argv[])
{
    while (gets(line)) {
        int len = strlen(line);
        if (len == 8) {//query
            sscanf(line, "%d:%d:%d", &hour, &minute, &second);
            printf("%s %.2lf km\n", line, cal());
        }
        else {
            sscanf(line, "%d:%d:%d %lf", &hour, &minute, &second, &speed);
            vp.push_back(make_pair(sec(), speed / 3.6));
        }
    }
    return 0;
}