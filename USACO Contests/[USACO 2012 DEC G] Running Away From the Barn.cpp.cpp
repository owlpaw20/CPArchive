#include <iostream>

#define endl '\n'

using std::cin;
using std::cout;

using i64 = long long;

const int MAX_N = 2e5 + 5;

int N, fa[MAX_N][20];
i64 T, depth[MAX_N], d[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> T;

  d[1] = 1;

  for (int i = 2, p; i <= N; ++i) {
    i64 w;
    cin >> p >> w;

    fa[i][0] = p;
    depth[i] = depth[p] + w;

    for (int j = 1; j <= 18; ++j)
      fa[i][j] = fa[fa[i][j - 1]][j - 1];

    int u = i;
    for (int j = 18; ~j; --j)
      if (depth[i] - depth[fa[u][j]] <= T)
        u = fa[u][j];

    ++d[i], --d[fa[u][0]];
  }

  for (int i = N; i; --i)
    d[fa[i][0]] += d[i];

  for (int i = 1; i <= N; ++i)
    cout << d[i] << endl;

  return fflush(stdout), 0;
}
