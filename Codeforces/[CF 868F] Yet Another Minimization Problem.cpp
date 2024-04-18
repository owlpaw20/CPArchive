#pragma GCC optimize("O2,unroll-loops")

#include <limits>
#include <iostream>
#include <unordered_map>

#define endl '\n'

using c32 = const int;
using i64 = long long int;
using u64 = unsigned long long int;

const int MAX_N = 1e5 + 5;
const int MAX_K = 25;

int n, k, a[MAX_N], kk;
i64 f[MAX_N][MAX_K];

int l = 1, r = 0, cnt[MAX_N];
i64 sum;

// 借用莫队思想对区间内的不同元素数量进行维护
inline i64 val(const int L, const int R) {
  while (l > L) sum += cnt[a[--l]]++;
  while (r < R) sum += cnt[a[++r]]++;
  while (l < L) sum -= --cnt[a[l++]];
  while (r > R) sum -= --cnt[a[r--]];
  return sum;
}

// 分治地利用决策单调性优化状态转移
// q_l 和 q_r 为维护状态转移的左右边界
// p_l 和 p_r 为最优决策点的左右边界
void divide_and_conquer(c32 q_l, c32 q_r, c32 p_l, c32 p_r) {
  c32 q_mid = (q_l + q_r) >> 1;

  int p = p_l;
  u64 min_val = std::numeric_limits<i64>::max();

  // 计算状态转移中点处的最优决策点
  for (int i = p; i <= std::min(p_r, q_mid); ++i) {
    u64 t = (u64)f[i - 1][kk - 1] + val(i, q_mid);
    if (t < min_val) min_val = t, p = i;
  }

  f[q_mid][kk] = min_val;

  // 根据计算出的新边界来分治地计算状态转移两边的最优决策点
  if (q_l < q_mid) divide_and_conquer(q_l, q_mid - 1, p_l, p);
  if (q_r > q_mid) divide_and_conquer(q_mid + 1, q_r, p, p_r);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
    f[i][0] = std::numeric_limits<i64>::max();
  }

  // 按顺序从对 k = 1 ~ k 的情况进行分治
  for (kk = 1; kk <= k; ++kk)
    divide_and_conquer(1, n, 1, n);

  std::cout << f[n][k] << endl;
  return fflush(stdout), 0;
}
