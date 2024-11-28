#pragma GCC optimize("O2,unroll-loops")
#include <bits/stdc++.h>

using f64 = double;
using TUP = std::tuple<f64, int, int>;

const int MAX_N = 55;

int N, M;
char mp[MAX_N][MAX_N];
f64 d[MAX_N][MAX_N];

inline f64 dist(int x1, int y1, int x2, int y2) {
  int dx = x2 - x1, dy = y2 - y1;
  return sqrt(dx * dx + dy * dy);
}

bool check(int x1, int y1, int x2, int y2) {
  for (int i = x1 + 1; i <= x2; ++i)
    for (int j = y1 + 1; j <= y2; ++j)
      if (mp[i][j] == '#') {
        f64 k1 = i - 1 == x1 ? 1e9 : (j - y1) * 1.0 / (i - 1 - x1);
        f64 k2 = x2 == x1 ? 1e9 : (y2 - y1) * 1.0 / (x2 - x1);
        f64 k3 = i == x1 ? 1e9 : (j - 1 - y1) * 1.0 / (i - x1);
        if (k1 >= k2 && k2 >= k3) return false;
      }

  return true;
}

void Dijkstra() {
  for (int i = 0; i <= N; ++i)
    for (int j = 0; j <= M; ++j)
      d[i][j] = 1e9;

  std::priority_queue<TUP, std::vector<TUP>, std::greater<TUP>> heap;
  heap.emplace(d[0][0] = 0, 0, 0);

  while (!heap.empty()) {
    auto [dd, x, y] = heap.top();
    heap.pop();

    for (int i = x; i <= N; ++i)
      for (int j = y; j <= M; ++j)
        if (i != x || j != y)
          if (x == i || y == j || check(x, y, i, j))
            if (f64 td = dd + dist(x, y, i, j); td < d[i][j])
              heap.emplace(d[i][j] = td, i, j);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= M; ++j)
      std::cin >> mp[i][j];

  Dijkstra();

  std::fixed(std::cout).precision(7);
  std::cout << d[N][M] << '\n';
  return 0;
}
