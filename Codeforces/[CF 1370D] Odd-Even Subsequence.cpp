#include <iostream>
#include <algorithm>

const int MAX_N = 2e5 + 5;

int N, K;
int a[MAX_N];

bool check(int mid, bool p) {
  bool flag = true;  // 子序列从下标 1 开始，1 是奇数

  for (int i = 1, left = N; i <= N; ++i, flag ^= 1)
    if (flag == p && a[i] > mid) {   // 如果当前位置大于 mid，则跳过当前元素
      flag ^= 1;                     // 以原序列下一个元素作为子序列中下一个元素
      if (--left < K) return false;  // 子序列长度必须大于 K
    }

  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> K;

  int l = 1, r = 0;
  for (int i = 1; i <= N; ++i) std::cin >> a[i], r = std::max(r, a[i]);

  while (l < r) {
    int mid = (l + r) >> 1;
    if (check(mid, 0) || check(mid, 1)) r = mid;
    else l = mid + 1;
  }

  std::cout << r << std::endl;
  return 0;
}
