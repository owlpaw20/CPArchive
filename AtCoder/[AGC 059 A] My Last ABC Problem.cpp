#include <bits/stdc++.h>

using PII = std::pair<int, int>;
using BLOCK = std::pair<char, PII>;

const int MAX_N = 1e5 + 5;

int N, q, bel[MAX_N];
std::vector<BLOCK> b;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> q;

  for (int i = 1; i <= N; ++i) {
    static char ch;
    std::cin >> ch;
    if (b.empty() || b.back().first != ch) b.emplace_back(ch, PII(i, i));
    else ++b.back().second.second;
    bel[i] = b.size() - 1;
  }

  while (q--) {
    static int l, r;
    std::cin >> l >> r;

    int cnt = bel[r] - bel[l] + 1;

    if (cnt == 1) std::cout << 0 << '\n';
    else if (cnt == 2) std::cout << 1 << '\n';
    else if (cnt % 2 == 0) std::cout << cnt / 2 << '\n';
    else if (cnt % 2 == 1) std::cout << cnt / 2 + (b[bel[l]].first != b[bel[r]].first) << '\n';
  }

  std::cout.flush();
  return 0;
}
