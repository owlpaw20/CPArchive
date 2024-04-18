#include <numeric>
#include <iostream>

#define endl '\n'

using u32 = unsigned int;

const int MAX_N = 1e5 + 5;
const int BUC_SIZE = 1 << 8;
const int BIT_MASK = BUC_SIZE - 1;

int N;
u32 x[MAX_N];

void radix_sort() {
  u32 *a = x;
  u32 *b = new u32[MAX_N];
  u32 *buc = new u32[BUC_SIZE];

  for (int i = 0; i < 32; i += 8) {
    std::fill(buc, buc + BUC_SIZE, 0);
    for (int j = 1; j <= N; ++j) ++buc[(a[j] >> i) & BIT_MASK];
    std::exclusive_scan(buc, buc + BUC_SIZE, buc, 0);
    for (int j = 1; j <= N; ++j) b[++buc[(a[j] >> i) & BIT_MASK]] = a[j];
    std::swap(a, b);
  }

  delete[] b, delete[] buc;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  for (int i = 1; i <= N; ++i)
    std::cin >> x[i];

  radix_sort();

  for (int i = 1; i <= N; ++i)
    std::cout << x[i] << ' ';

  std::cout << endl;
  return fflush(stdout), 0;
}
