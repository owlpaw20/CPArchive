#include <bits/stdc++.h>

using u32 = unsigned int;

const int MAX_N = 200'005;
const int MAX_S = 1 << 26;

int N, f[MAX_S + 5];
std::string s;
u32 p[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> s;
  N = s.length(), s = '\0' + s;
  for (int i = 1; i <= N; ++i) p[i] = p[i - 1] xor (1 << (s[i] - 'a'));

  memset(f, 0x3F, sizeof f);
  f[0] = 0;

  for (int i = 1; i <= N; ++i)
    for (int j = 0; j < 26; ++j)
      f[p[i]] = std::min(f[p[i]], f[p[i] xor (1 << j)] + 1);

  f[0] = 1;
  std::cout << f[p[N]] << '\n';
  return 0;
}
