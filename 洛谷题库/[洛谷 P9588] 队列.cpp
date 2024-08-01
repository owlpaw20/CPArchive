#include <bits/stdc++.h>

using LL = long long;

const int MAX_N = 2e5 + 5;

int cnt, hh, tt;
LL sum[MAX_N], loc[MAX_N];
LL dq[MAX_N], d;

int main() {
  int q;
  std::cin >> q >> q;

  while (q--) {
    static LL x, type;
    std::cin >> type;

    switch (type) {
      case 1:
        std::cin >> x;
        sum[cnt + 1] = sum[cnt] + x, ++cnt;    // 计算所加入段的长度的前缀和
        while (hh <= tt && dq[tt] <= x) --tt;  // 将不可能成为最大值的弹出单调队列
        dq[++tt] = x;                          // 将当前段加入队列
        loc[tt] = sum[cnt];                    // 保存队尾位置的前缀和
        break;

      case 2:
        std::cin >> x;
        d += x;  // 统计已经删除的元素个数
        break;

      case 3:
        std::cin >> x;
        std::cout << d + x - sum[std::lower_bound(sum + 1, sum + cnt, d + x) - sum - 1] << '\n';  // 通过前缀和剔除掉已经被弹出的元素
        break;

      case 4:
        while (hh <= tt && loc[hh] <= d) ++hh;  // 将已经被弹出的元素弹出单调队列
        std::cout << dq[hh] << '\n';            // 输出剔除后作为队首的最大元素
        break;
    }
  }

  std::cout.flush();
  return 0;
}
