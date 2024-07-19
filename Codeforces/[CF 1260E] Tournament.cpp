#include <cmath>
#include <queue>
#include <iostream>

using LL = long long;

const int MAX_N = 1 << 18;

int N, a[MAX_N + 5];
std::priority_queue<int, std::vector<int>, std::greater<int>> heap;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  LL ans = 0;

  for (int i = N; i; --i) {
    if (a[i] == -1) break;
    heap.push(a[i]);
    if (ceil(log2(i)) == floor(log2(i)))
      ans += heap.top(), heap.pop();
  }

  std::cout << ans << std::endl;
  return 0;
}
