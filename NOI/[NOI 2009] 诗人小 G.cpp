#include <cmath>
#include <string>
#include <iostream>

#define endl '\n'

using str = std::string;
using f128 = long double;  // 由于数字较大，采用 long double 存储

const int MAX_N = 1e5 + 5;

int n, L, P;
str s[MAX_N];
int sum_len[MAX_N];

int qh, qr;
struct Data {
  int j, l, r;  // j 为最优决策点的下标，l 和 r 为该决策作为最优决策的影响范围
  Data() {}
  Data(int _j, int _l, int _r) : j(_j), l(_l), r(_r) {}
} q[MAX_N];

f128 f[MAX_N];   // f[i] = 对前 i 句诗排版的最小不协调度
int opt[MAX_N];  // opt[i] = 存储 f[i] 时的最优决策点位置

// f[i] = min{f[j] + abs(sum_len[i] - sum_len[j]) + (i - j - 1) - L)^P}
// 令 val(j, i) = f[j] + abs(sum_len[i] - sum_len[j]) + (i - j - 1) - L)^P
// 则 f[i] = min{val[j, i]}

inline f128 val(const int j, const int i) {
  f128 ret = 1, v = fabsl(sum_len[i] - sum_len[j] + i - j - 1 - L);
  for (int i = 0; i < P; ++i) ret *= v;  // 用 pow 会 TLE
  return ret + f[j];
}

void solve() {
  std::cin >> n >> L >> P;
  for (int i = n; i >= 1; --i) std::cin >> s[i];  // 倒序存储是为了输出方案
  for (int i = 1; i <= n; ++i) sum_len[i] = sum_len[i - 1] + s[i].length();

  qh = 0, qr = 0;
  q[0] = Data(0, 1, n);  // 初始情况下，所有下标的最优决策点均为 0

  for (int i = 1; i <= n; ++i) {
    if (q[qh].r == i - 1) ++qh;  // 如果队首的决策已经过时，则可以弹出队列
    else q[qh].l = i;            // 如果队列中存在 i 以前的元素，则不必考虑

    opt[i] = q[qh].j;       // 记录最优决策点
    f[i] = val(opt[i], i);  // 执行状态转移

    int pos = -1;  // 用于标记当前决策是否能够取代此前较劣的决策，并标记更优决策的左端点

    // 将决策不优的位于队列末端的决策剔除
    while (qh <= qr && val(q[qr].j, q[qr].l) >= val(i, q[qr].l)) pos = q[qr--].l;

    // 如果对于队列末端的决策来说，其左端点优于 i，右端点劣于 i，则通过二分来确定需要覆盖的位置
    if (qh <= qr && val(q[qr].j, q[qr].r) >= val(i, q[qr].r)) {
      int l = q[qr].l, r = q[qr].r, j = q[qr].j;

      while (l < r) {
        int mid = (l + r) >> 1;
        // 如果 i 到二分中点的决策优于队尾的决策，则需要覆盖的点应该在左半边
        // 否则在右半边
        if (val(j, mid) >= val(i, mid)) r = mid;
        else l = mid + 1;
      }

      q[qr].r = r - 1;  // 队尾元素在 r 之前的所有决策都比 i 更优，更新其右端点
      pos = r;          // 设置 i 处决策的左端点
    }

    // 如果存在不优的决策，则用 i 进行覆盖
    if (pos != -1) q[++qr] = Data(i, pos, n);
  }

  if (f[n] > 1e18) {
    std::cout << "Too hard to arrange" << endl;
    std::cout << "--------------------" << endl;
    return;
  }

  std::cout << (long long)f[n] << endl;

  for (int i = n; i >= 1; i = opt[i]) {  // 根据最优决策点进行倒推
    for (int j = i; j > opt[i]; --j) {   // 将 i 与最优决策点之间的字符串作为一行输出
      std::cout << s[j];
      if (j != opt[i] + 1) std::cout.put(' ');  // 空格严判
    }
    std::cout.put('\n');
  }

  std::cout << "--------------------" << endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;
  while (t--) solve();

  return fflush(stdout), 0;
}
