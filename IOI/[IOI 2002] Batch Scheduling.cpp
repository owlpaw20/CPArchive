#include <iostream>

#define endl '\n'

using i64 = long long int;
using i128 = __int128_t;

const int MAX_N = 1e4 + 5;

int n, s;
int t[MAX_N], c[MAX_N];
int sum_t[MAX_N], sum_c[MAX_N];

i64 f[MAX_N];
int q[MAX_N];  // 存储凸包下边界的斜率的单调队列，从队首到队尾单调递增

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> s;

  for (int i = 1; i <= n; ++i) {
    std::cin >> t[i] >> c[i];
    sum_t[i] = sum_t[i - 1] + t[i];
    sum_c[i] = sum_c[i - 1] + c[i];
  }

  int qh = 0, qr = 0;
  q[0] = 0;

  // 对于每一个新的 i，从队首删除小于（等于与否均可）当前 i 斜率的斜率
  auto eliminate_front = [&](const int i) -> bool {
    const int h = q[qh], hx = q[qh + 1];
    return (f[hx] - f[h]) <= i64(sum_t[i] + s) * (sum_c[hx] - sum_c[h]);
  };

  // 从队尾删除大于新增斜率的斜率，维护凸包下边界合法性
  auto eliminate_back = [&](const int i) -> bool {
    const int r = q[qr], rp = q[qr - 1];
    return i128(f[r] - f[rp]) * (sum_c[i] - sum_c[rp]) >= i128(f[i] - f[rp]) * (sum_c[r] - sum_c[rp]);
  };

  for (int i = 1; i <= n; ++i) {
    while (qh < qr && eliminate_front(i)) ++qh;
    f[i] = f[q[qh]] - i64(sum_t[i] + s) * sum_c[q[qh]] + (i64)sum_c[i] * sum_t[i] + (i64)sum_c[n] * s;
    while (qh < qr && eliminate_back(i)) --qr;
    q[++qr] = i;
  }

  std::cout << f[n] << endl;
  return fflush(stdout), 0;
}
