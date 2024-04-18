#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

using i64 = unsigned long long;

string ans;
int n, idx;
i64 k, bin[70];

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> k;
  while (k)
    bin[++idx] = k % 2, k /= 2;
  for (int i = 1; i <= n; i++)
    if (bin[i + 1] == bin[i])
      ans[i] = '0';
    else
      ans[i] = '1';
  for (int i = n; i > 0; i--)
    cout << ans[i];
  cout << endl;
  return 0;
}
