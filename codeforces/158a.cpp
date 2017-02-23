#include <cstdio>

int main()
{
  int n, k;
  scanf("%d%d", &n, &k);
  int arr[64];
  for (int i=1; i<=n; i++) {
    scanf("%d", &arr[i]);
  }

  if (arr[k] <= 0) {
    while (k>0 && arr[k] <= 0) {
      k--;
    }
  } else {
    while (k<n && arr[k+1] == arr[k]) {
      k++;
    }
  }
  printf("%d", k);
  return 0;
}
