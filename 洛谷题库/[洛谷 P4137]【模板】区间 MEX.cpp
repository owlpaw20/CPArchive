#include <tuple>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'

using std::cin;
using std::cout;
using std::get;
using std::vector;

const int MAX_N = 2e5 + 5;

using TUP = std::tuple<int, int, int>;

int N, M;
int a[MAX_N];
vector<TUP> queries;
int res[MAX_N];

struct SEGTREE {
  int node[MAX_N << 2];

  void update(int x, int v, int u = 1, int nl = 1, int nr = N + 1) {
    if (nl == nr) {
      node[u] = v;
      return;
    }

    int mid = (nl + nr) >> 1;

    if (x <= mid)
      update(x, v, u << 1, nl, mid);
    else
      update(x, v, u << 1 | 1, mid + 1, nr);

    node[u] = std::min(node[u << 1], node[u << 1 | 1]);
  }

  int query(int v, int u = 1, int nl = 1, int nr = N + 1) {
    if (nl == nr) return nl;

    int mid = (nl + nr) >> 1;

    if (node[u << 1] < v) return query(v, u << 1, nl, mid);
    return query(v, u << 1 | 1, mid + 1, nr);
  }
} SGT;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);

  memset(SGT.node, -1, sizeof SGT.node);

  cin >> N >> M;
  for (int i = 1; i <= N; ++i) cin >> a[i], ++a[i];

  queries.resize(M);
  for (auto& [l, r, i] : queries) cin >> l >> r;
  for (int i = 0; i < M; ++i) get<2>(queries[i]) = i;

  std::sort(queries.begin(), queries.end(),
    [&](const TUP a, const TUP b) {
      return get<1>(a) < get<1>(b);
    });

  for (int i = 1, j = 0; i <= N; ++i) {
    if (a[i] <= N) SGT.update(a[i], i);
    while (j < M && get<1>(queries[j]) == i)
      res[get<2>(queries[j])] = SGT.query(get<0>(queries[j])), ++j;
  }

  for (int i = 0; i < M; ++i) cout << res[i] - 1 << endl;
  return fflush(stdout), 0;
}
