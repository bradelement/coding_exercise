#include <cstdio>
#include <cstring>

int main()
{
  int n;
  scanf("%d", &n);

  char s[128];
  while (n--) {
    scanf("%s", s);
    int len = strlen(s);
    if (len > 10) {
      printf("%c", s[0]);
      printf("%d", len-2);
      printf("%c\n", s[len-1]);
    } else {
      printf("%s\n", s);
    }
  }

  return 0;
}
