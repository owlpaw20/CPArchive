#include <bits/stdc++.h>

const int MAX_N = 5e5 + 5;

using i64 = long long;
using f64 = double;

i64 L, c[MAX_N];
int a, b, t, r, N;

f64 f[MAX_N], g[MAX_N];  // f[i] 表示到达第 i 个咖啡馆并购买咖啡所需要的时间
int pv[MAX_N];

std::deque<int> dq;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> L >> a >> b >> t >> r >> N;
  for (int i = 1; i <= N; ++i) std::cin >> c[i];

  int cool = a * t;
  int boost = a * t + b * r;

  // 对于间隔超过冷却并加速的总距离的两家咖啡馆
  f64 minD = 1e18;   // 动态维护 [1, i] 最小的 -(c[j] + boost / a + t + r + f[j]) 便于转移
  int minD_pos = 0;  // 最优转移点的位置

  // 记录最末转移点
  f64 ans = L * 1.0 / a;
  int fn_state = 0;

  for (int i = 1, j = 1, k = 1; i <= N; ++i) {
    f[i] = c[i] * 1.0 / a;  // 初始化

    // 尝试对间隔超过冷却和加速总距离的咖啡馆进行转移
    while (j < i && c[i] - c[j] >= boost) {
      f64 tmp = -(c[j] + boost) * 1.0 / a + t + r + f[j];
      if (tmp < minD) minD = tmp, minD_pos = j;
      ++j;
    }

    if (minD_pos && minD + c[i] * 1.0 / a < f[i]) {
      f[i] = minD + c[i] * 1.0 / a;
      pv[i] = minD_pos;
    }

    // 尝试对间隔超过冷却距离但不超过加速距离的咖啡馆进行转移，需要用到单调队列
    while (k < i && c[i] - c[k] >= cool) {
      g[k] = -(c[k] + cool) * 1.0 / b + t + f[k];
      while (!dq.empty() && g[dq.back()] > g[k]) dq.pop_back();
      dq.push_back(k++);
    }

    while (!dq.empty() && c[i] - c[dq.front()] > boost) dq.pop_front();

    if (!dq.empty() && g[dq.front()] + c[i] * 1.0 / b < f[i]) {
      f[i] = g[dq.front()] + c[i] * 1.0 / b;
      pv[i] = dq.front();
    }

    // 计算当前位置作为最末转移点的答案
    f64 fn_cost;
    if (L - c[i] <= cool) fn_cost = (L - c[i]) * 1.0 / a;
    else if (L - c[i] <= boost) fn_cost = (L - c[i] - cool) * 1.0 / b + t;
    else fn_cost = (L - c[i] - boost) * 1.0 / a + t + r;

    if (f[i] + fn_cost < ans) {
      ans = f[i] + fn_cost;
      fn_state = i;
    }
  }

  // 记录转移路径
  std::vector<int> t;
  while (fn_state) t.push_back(fn_state), fn_state = pv[fn_state];

  std::cout << t.size() << '\n';
  for (auto it = t.rbegin(); it != t.rend(); ++it) std::cout << *it - 1 << ' ';

  std::cout.flush();
  return 0;
}
