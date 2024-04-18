#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
#define endl '\n'
using namespace std;
using EDGE = tuple<int, int, int>;

struct DisjointSet {
  vector<int> p;
  void init(int n) {
    p.clear();
    p.resize(n + 1);
    for (int i = 1; i <= n; i++)
      p[i] = i;
  }
  int find(int x) {
    if (p[x] == x) return x;
    return p[x] = find(p[x]);
  }
  bool merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    return p[x] = y, true;
  }
};

int n, m;
DisjointSet DSU;
vector<EDGE> edges;

int Kruskal() {
  int ans = 0;
  for (EDGE e : edges) {
    auto [u, v, w] = e;
    u = DSU.find(u);
    v = DSU.find(v);
    if (DSU.merge(u, v)) ans += w;
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  DSU.init(n);

  int mandatory_cost = 0;
  int p, u, v, w;
  while (m--) {
    cin >> p >> u >> v >> w;
    if (p == 1) {
      DSU.merge(u, v);
      mandatory_cost += w;
    } else
      edges.emplace_back(u, v, w);
  }

  auto cmp = [](EDGE a, EDGE b) {
    return get<2>(a) < get<2>(b);
  };
  sort(edges.begin(), edges.end(), cmp);

  cout << mandatory_cost + Kruskal() << endl;

  fflush(stdout);
  return 0;
}
