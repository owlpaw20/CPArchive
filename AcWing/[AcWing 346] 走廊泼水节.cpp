#include <tuple>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using TPL = tuple<int, int, int>;

struct UnionFind {
  vector<int> fa;
  vector<int> sz;

  void reset(int n) {
    fa.resize(n);
    sz.assign(n, 1);
    iota(fa.begin(), fa.end(), 0);
  }

  int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
  }

  bool merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    return fa[x] = y, sz[y] += sz[x], true;
  }
};

int T;
UnionFind DS;
vector<TPL> edges;

auto cmp = [](TPL x, TPL y) {
  return get<2>(x) < get<2>(y);
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    DS.reset(n + 5);
    edges.clear();

    for (int i = 1, u, v, w; i < n; i++) {
      cin >> u >> v >> w;
      edges.emplace_back(u, v, w);
    }

    sort(edges.begin(), edges.end(), cmp);

    int ans = 0;

    for (auto [u, v, w] : edges) {
      u = DS.find(u), v = DS.find(v);
      if (u != v) {
        ans += (DS.sz[u] * DS.sz[v] - 1) * (w + 1);
        DS.merge(u, v);
      }
    }

    cout << ans << endl;
  }

  fflush(stdout);
  return 0;
}
