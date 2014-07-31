#include <cstdio>
#include <cmath>

//http://algorithmist.com/index.php/UVa_10900
double cal(int n, double t, int cur) {
    if (cur == 0) return pow(2, n);

    double cur_money = pow(2, n-cur);
    double next_money = cal(n, t, cur-1);
    double lim = cur_money / next_money;

    //这其实是个积分.. 
    //对任意给定的p, best_strategy得到的结果应该是max(cur_money, p*next_money)
    //p在[t, 1]均匀分布, 分开讨论
    if (lim <= t) {
        return next_money * (1 + t) / 2;
    }
    else {
        double numerator = cur_money*(lim-t) + next_money*(0.5-0.5*lim*lim);
        return numerator / (1-t);
    }
}

int main()
{
    int n;
    double t;

    while (scanf("%d%lf", &n, &t), n) { 
        printf("%.3lf\n", cal(n, t, n));
    }

    return 0;
}
