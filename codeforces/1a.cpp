#include <cstdio>
#include <cmath>

int main()
{
  int n, m, a;

  scanf("%d%d%d", &n, &m, &a);
  printf("%.0lf", ceil(n*1.0/a) * ceil(m*1.0/a));

  return 0;
}
