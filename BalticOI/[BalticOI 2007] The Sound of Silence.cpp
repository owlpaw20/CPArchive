#include <vector>
#include <climits>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

struct SparseTable {
  using VI = vector<int>;

  int limit;
  int ST[2][(int)1e6 + 1][14];

  int log2(int x) {
    int ret = 0;
    while (x >>= 1) ret += 1;
    return ret;
  }

  void init(int n, int m, VI v) {
    limit = log2(m);
    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= limit; j++)
        ST[1][i][j] = INT_MAX;
    for (int i = 1; i <= n; i++)
      ST[0][i][0] = ST[1][i][0] = v[i];
    for (int j = 1; j <= limit; j++)
      for (int i = 1; i + (1 << j) - 1 <= n; i++)
        ST[0][i][j] = max(ST[0][i][j - 1], ST[0][i + (1 << (j - 1))][j - 1]),
        ST[1][i][j] = min(ST[1][i][j - 1], ST[1][i + (1 << (j - 1))][j - 1]);
  }
  PII query(int l, int r) {
    int t = log2(r - l + 1);
    int a = max(ST[0][l][t], ST[0][r - (1 << t) + 1][t]),
        b = min(ST[1][l][t], ST[1][r - (1 << t) + 1][t]);
    return make_pair(a, b);
  }
};

int n, m, c;
vector<int> a;
SparseTable ST;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m >> c;
  a.resize(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> a[i];

  ST.init(n, m, a);

  bool flag = false;
  for (int i = 1; i + m - 1 <= n; i++) {
    auto [mx, mn] = ST.query(i, i + m - 1);
    if (mx - mn <= c)
      cout << i << endl, flag = true;
  }

  if (!flag) puts("NONE");
  fflush(stdout);
  return 0;
}
