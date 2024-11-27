#include <algorithm>
#include <iostream>
#include <vector>

using u64 = unsigned long long;
using u128 = __uint128_t;

const int MAX_N = 20;
const u64 MAX_V = 1'000'000'000'000'000'000;

int N, p[MAX_N], K;
std::vector<u64> set_A, set_B;

void DFS_set_A(const int i, u128 prod) {
  set_A.push_back(prod);
  if (i > N) return;

  do {
    DFS_set_A(i + 2, prod);
    prod *= p[i];
  } while (prod <= MAX_V);
}

void DFS_set_B(const int i, u128 prod) {
  set_B.push_back(prod);
  if (i > N) return;

  do {
    DFS_set_B(i + 2, prod);
    prod *= p[i];
  } while (prod <= MAX_V);
}

bool check(const u64 x) {
  int cnt = 0;
  int b = set_B.size() - 1;

  for (u64 a : set_A) {
    while (~b && a * set_B[b] > x) --b;
    cnt += b + 1;
  }

  return cnt >= K;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> p[i];

  std::cin >> K;

  DFS_set_A(1, 1);
  DFS_set_B(2, 1);

  std::sort(set_A.begin(), set_A.end());
  std::sort(set_B.begin(), set_B.end());
  set_A.erase(std::unique(set_A.begin(), set_A.end()), set_A.end());
  set_B.erase(std::unique(set_B.begin(), set_B.end()), set_B.end());

  u64 l = 0, r = MAX_V, mid;
  while (l < r) check(mid = (l + r) >> 1) ? (r = mid) : (l = mid + 1);

  std::cout << r << '\n';
  return 0;
}
