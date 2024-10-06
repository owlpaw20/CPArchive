#include <bits/stdc++.h>

int N;

void solve() {
  std::cin >> N;

  std::priority_queue<int, std::vector<int>, std::greater<int>> heap;
  for (int i = 1, x; i <= N; ++i) std::cin >> x, heap.push(x);

  while (heap.size() > 1) {
    static int x, y;
    x = heap.top(), heap.pop();
    y = heap.top(), heap.pop();
    heap.push((x + y) >> 1);
  }

  std::cout << heap.top() << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  std::cout.flush();
  return 0;
}
