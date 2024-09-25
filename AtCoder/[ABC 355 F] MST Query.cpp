#include <bits/stdc++.h>

const int MAX_N = 2e5 + 5;
const int MAX_W = 15;

int N, q;

struct UnionFind {
  int fa[MAX_N], e_cnt;
  void init(int x) { std::iota(fa, fa + x + 1, 0), e_cnt = 0; }
  int find(int x) { return fa[x] ^ x ? fa[x] = find(fa[x]) : x; }
  bool merge(int x, int y) { return (x = find(x)) ^ (y = find(y)) && (fa[x] = y, ++e_cnt, true); }
} dsu[MAX_W];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> q;
  for (int i = 1; i <= 10; ++i) dsu[i].init(N);

  for (int i = 1, u, v, w; i < N; ++i) {
    std::cin >> u >> v >> w;
    // 加入这条边可能影响到存在包含相同或更大边权的答案
    for (int j = w; j <= 10; ++j) dsu[j].merge(u, v);
  }

  while (q--) {
    static int u, v, w, ans = 0;
    std::cin >> u >> v >> w;
    for (int i = w; i <= 10; ++i) dsu[i].merge(u, v);

    // 当前边权的集合内所有连边中没有被更小边权取代的边的总权值就是当前边权的总贡献
    for (int i = 1; i <= 10; ++i) ans += (dsu[i].e_cnt - dsu[i - 1].e_cnt) * i;
    std::cout << ans << '\n', ans = 0;
  }

  std::cout.flush();
  return 0;
}
