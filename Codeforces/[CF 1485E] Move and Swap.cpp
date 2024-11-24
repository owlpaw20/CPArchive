#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 200'005;

int N;
int a[MAX_N];
std::vector<std::vector<int>> gg;

i64 f[MAX_N];
int fa[MAX_N], d[MAX_N], maxD;
std::vector<std::vector<int>> ver;

/**********
  设 f[i] 表示一次操作完成后红子在 i 处时的最大答案。
  蓝子由于可以在下面一层任意节点，所以不必多加考虑。

  考虑转移。一次操作最后一步是将红蓝子交换，因此可以考虑交换和不交换两种情况。

  如果不交换，则红子在当前位置 i。
  根据贪心，蓝子一定在当前深度所有节点中权值最大或最小的节点上，才能使得这一步答案最优。
  可以维护当前层所有节点的权值最大值和最小值进行。

  如果交换，则蓝子在当前位置 i，不妨设蓝子原来在位置 j，则交换后红子在位置 j，设 fa 为 i 的父节点。
  考虑转移。f[j] <- max{f[fa] + abs(a[i] - a[j])} <=> f[fa] + max{abs(a[i] - a[j])}。
  考虑拆开绝对值，f[j] <- max{max(f[fa] + a[i] - a[j], f[fa] - a[i] + a[j])}。
  维护同一深度下的 f[fa] + a[i] 和 f[fa] - a[i] 各自的最大值即可。
**********/

void BFS() {
  memset(d, 0, sizeof(int) * (N + 1));
  ver = std::vector<std::vector<int>>(N + 1);

  f[1] = 0;
  ver[0].push_back(1);

  std::queue<int> q;
  for (int v : gg[1]) q.push(v), fa[v] = 1, ver[d[v] = 1].push_back(v);

  int preD = 0;
  int maxA = 0, minA = std::numeric_limits<int>::max();
  i64 maxFPA = std::numeric_limits<i64>::min(), maxFMA = maxFPA;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    if (d[u] != preD) {
      maxA = 0, minA = std::numeric_limits<int>::max();
      maxFPA = maxFMA = std::numeric_limits<i64>::min();

      for (int v : ver[d[u]]) {
        maxA = std::max(maxA, a[v]);
        minA = std::min(minA, a[v]);
        maxFPA = std::max(maxFPA, f[fa[v]] + a[v]);
        maxFMA = std::max(maxFMA, f[fa[v]] - a[v]);
      }
    }

    preD = d[u];
    maxD = std::max(maxD, d[u]);

    f[u] = f[fa[u]] + std::max(maxA - a[u], a[u] - minA);
    f[u] = std::max({f[u], maxFPA - a[u], maxFMA + a[u]});

    for (int v : gg[u])
      if (!d[v] && v != 1)
        q.push(v), fa[v] = u, ver[d[v] = d[u] + 1].push_back(v);
  }
}

void solve() {
  std::cin >> N, maxD = 0;
  gg = std::vector<std::vector<int>>(N + 1);

  for (int i = 2, x; i <= N; ++i) {
    std::cin >> x;
    gg[i].push_back(x);
    gg[x].push_back(i);
  }

  for (int i = 2; i <= N; ++i) std::cin >> a[i];

  BFS();

  i64 ans = 0;
  for (int v : ver[maxD]) ans = std::max(ans, f[v]);
  std::cout << ans << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return 0;
}
