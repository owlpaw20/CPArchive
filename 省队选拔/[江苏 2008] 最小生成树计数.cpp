#include <cstring>
#include <numeric>
#include <iostream>
#include <algorithm>

using PII = std::pair<int, int>;

const int MAX_V = 1e2 + 5;
const int MAX_E = 1e3 + 5;
const int INF = 2e9;
const int MOD = 31011;

int N, M;

struct Edge {
  int st, fn, wt;
  bool operator<(const Edge& x) const { return wt < x.wt; }
} E[MAX_E];

PII seg[MAX_E];
int bel[MAX_E], idx;
int cnt[MAX_E], cnt_t;

struct UnionFind {
  int fa[MAX_V];
  void init(int x) { std::iota(fa + 1, fa + x + 1, 1); }
  int find(int x) { return (x == fa[x]) ? x : (fa[x] = find(fa[x])); }
  bool merge(int x, int y) { return ((x = find(x)) != (y = find(y))) && (fa[x] = y, true); }
} sets;

bool Kruskal() {
  int cnt_e = 0;
  for (int i = 1; i <= M; ++i) {
    if (cnt_e == N - 1) break;
    if (sets.merge(E[i].st, E[i].fn))
      ++cnt[bel[i]], ++cnt_e;  // 统计形成生成树所需要每一种边权的边各多少条
  }
  return cnt_e == N - 1;
}

// 暴搜以统计每一段相同边权的边内所选条数的情况
void DFS(int i, int j, int e) {
  if (e > cnt[j]) return;  // 如果当前所选边数已经超过了目标值，则一定会成环，直接结束递归

  if (i > seg[j].second) {     // 如果已经选到了当前段的边界处
    if (e == cnt[j]) ++cnt_t;  // 如果所选边可以组成生成树，就计入答案
    return;
  }

  // 选入这条边的情况
  int tmp[MAX_V];
  memcpy(tmp, sets.fa, sizeof(int) * (N + 1));             // 对并查集数组进行备份
  if (sets.merge(E[i].st, E[i].fn)) DFS(i + 1, j, e + 1);  // 如果选入这条边不会成环，则选入
  memcpy(sets.fa, tmp, sizeof(int) * (N + 1));             // 回溯

  // 不选这条边的情况
  DFS(i + 1, j, e);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  for (int i = 1; i <= M; ++i) std::cin >> E[i].st >> E[i].fn >> E[i].wt;

  std::sort(E + 1, E + M + 1);
  sets.init(N);

  // 将边权相同的边处理为一段
  E[0].wt = -INF, idx = 0;
  for (int i = 1; i <= M; ++i)
    E[i].wt == E[i - 1].wt ? void(++seg[idx].second) : void(seg[++idx] = PII(i, i)), bel[i] = idx;

  // 特判图不连通的情况
  if (!Kruskal()) {
    std::cout << 0 << '\n';
    return fflush(stdout), 0;
  }

  // 重置并查集
  sets.init(N);

  int ans = 1;  // 利用乘法原理求值，初始值为 1

  for (int i = 1; i <= idx; ++i)  // 从小到大枚举所有边权段以满足最小生成树的性质
    if (cnt[i]) {
      cnt_t = 0;
      DFS(seg[i].first, i, 0);  // 搜索当前段内边的选择情况
      (ans *= cnt_t) %= MOD;    // 乘法原理统计答案

      for (int j = seg[i].first; j <= seg[i].second; ++j)
        sets.merge(E[j].st, E[j].fn);  // 将当前边权段内的边加入生成树中
    }

  std::cout << ans << '\n';
  return fflush(stdout), 0;
}
