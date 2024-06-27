#include <numeric>
#include <iostream>

const int MAX_N = 1e6 + 5;

int N, M, p, q;
int c[MAX_N];

struct UnionFind {
  int fa[MAX_N];
  void init(int x) { std::iota(fa, fa + x + 1, 0); }
  int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
} dsu;  // 并查集中 find(x) 表示 x 后面第一个可以染色的元素

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M >> p >> q;
  dsu.init(N);

  for (int i = M, l, r; i; --i) {
    l = (i * p + q) % N + 1, r = (i * q + p) % N + 1;
    if (l > r) std::swap(l, r);
    for (int j = r; j >= l;) {
      if (dsu.find(j) == j) c[j] = i, dsu.fa[j] = dsu.find(j - 1);
      j = dsu.fa[j];
    }
  }

  for (int i = 1; i <= N; ++i) std::cout << c[i] << '\n';
  std::cout.flush();
  return 0;
}
