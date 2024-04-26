#include <string>
#include <iostream>

#define endl '\n'

using u64 = unsigned long long;

const int MAX_S = 1e6 + 10;
const u64 BASE = 13331;
const u64 MOD = 13131331;

std::string s;

int lazy = 1;
u64 base[MAX_S] = {1};

inline void prep(int x) {
  while (lazy <= x)
    base[lazy] = base[lazy - 1] * BASE % MOD, ++lazy;
}

void solve(const int tc) {
  std::cin >> s;
  int n = s.length();

  prep(n);

  int ans = 0;
  u64 pre = 0, suf = 0;

  for (int i = 0; i < n - 1; ++i) {
    (pre += s[i] * base[i]) %= MOD;
    (suf = suf * BASE + s[n - i - 1]) %= MOD;
    ans += (pre == suf);
  }

  printf("Case %d: %d\n", tc, ans);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  for (int i = 1; i <= T; ++i) solve(i);

  fflush(stdout);
  return 0;
}
