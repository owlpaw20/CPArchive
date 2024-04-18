#include <cmath>
#include <string>
#include <iostream>

#define endl '\n'

using namespace std;

string s;
int cnt[26];

bool is_prime(int x) {
  int lmt = sqrt(x);
  if (x < 2) return false;
  for (int i = 2; i <= lmt; i++)
    if (x % i == 0)
      return false;
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> s;
  for (char ch : s)
    cnt[ch - 'a']++;

  int maxn = -1, minn = 101;
  for (int i = 0; i < 26; i++)
    if (cnt[i])
      maxn = max(maxn, cnt[i]), minn = min(minn, cnt[i]);

  int delta = maxn - minn;

  if (is_prime(delta)) {
    puts("Lucky Word");
    printf("%d\n", delta);
  } else
    puts("No Answer\n0");

  fflush(stdout);
  return 0;
}
