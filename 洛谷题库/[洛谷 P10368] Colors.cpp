#include <bitset>
#include <string>
#include <iostream>

#define endl '\n'

using l64 = long long;

const int MAX_N = 1e7 + 5;

std::string str1, str2;
std::bitset<MAX_N> del1, del2;

void solve() {
  int n;
  l64 K;
  std::cin >> n >> K >> str1;

  if (K == 0) {
    std::cout << str1 << endl;
    return;
  }

  if (K >= 1) {
    for (int i = 0; i < n; ++i) del1.reset(i);
    str2 = "";

    for (int i = 1; i < n - 1; ++i)
      if (str1[i - 1] == str1[i + 1])
        del1.set(i);

    for (int i = 0; i < n; ++i)
      if (!del1.test(i))
        str2.push_back(str1[i]);

    if (K == 1)
      return std::cout << str2 << endl, void();
  }

  n = str2.length();
  for (int i = 0; i < n; ++i) del2.reset(i);

  for (int i = 1; i < n - 1; ++i)
    if (str2[i - 1] == str2[i + 1])
      del2.set(i);

  for (int i = 0; i < n; ++i)
    if (!del2.test(i))
      std::cout << str2[i];

  std::cout << endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T, id;
  std::cin >> T >> id;
  while (T--) solve();

  return fflush(stdout), 0;
}
