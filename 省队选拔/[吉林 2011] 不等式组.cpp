#include <cmath>
#include <string>
#include <iostream>

using FL = double;

const int MAX_N = 1e5 + 5;
const int MAX_K = 1e6 + 5;
const int LIMIT = 1e6;
const int SHIFT = 1e6 + 1;
const int MAX_V = 2e6 + 1;

enum Condition {
  REMOVED = -2,  // 该表达式已被删除
  FALSE = -1,    // 恒不成立
  UNDEF = 0,     // 初始化状态
  TRUE = 1,      // 恒成立
  LESS = 2,      // 斜率 < 0
  GREATER = 3,   // 斜率 > 0
} cond[MAX_N];

int cnt, idx;
int zero[MAX_N];

// c1：所有斜率 > 0 的函数零点
// c2：所有斜率 < 0 的函数零点
int c1[MAX_K << 1], c2[MAX_K << 1];

struct Fenwick {
  template <int *c>
  void upd(int x, int v) {
    for (; x <= MAX_V; x += (x & -x))
      c[x] += v;
  }

  template <int *c>
  int sum(int x) {
    int ret = 0;
    for (; x; x -= (x & -x)) ret += c[x];
    return ret;
  }
} FWK;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int Q;
  std::cin >> Q;

  auto get_zero = [](int a, int b, int c) -> FL { return (c - b) * 1. / a; };

  while (Q--) {
    static std::string type;
    static int a, b, c;

    std::cin >> type >> a;
    (type == "Add") && (std::cin >> b >> c);

    if (type == "Add") {
      // 当斜率 < 0 时，x < (c - b) / a
      if (a < 0) {
        zero[++idx] = ceil(get_zero(a, b, c));                     // 求零点
        if (zero[idx] > LIMIT) ++cnt, cond[idx] = TRUE;            // 零点大于查询的上界，则恒成立
        else if (zero[idx] < -LIMIT) cond[idx] = FALSE;            // 零点小于查询的下界，则恒不成立
        else FWK.upd<c2>(zero[idx] + SHIFT, 1), cond[idx] = LESS;  // 零点在查询范围内，则保存到对应的树状数组中
      }

      // 当斜率 > 0 时，x > (c - b) / a
      else if (a > 0) {
        zero[++idx] = floor(get_zero(a, b, c));                       // 求零点
        if (zero[idx] < -LIMIT) ++cnt, cond[idx] = TRUE;              // 零点小于查询的下界，则恒成立
        else if (zero[idx] > LIMIT) cond[idx] = FALSE;                // 零点大于查询的上界，则恒不成立
        else FWK.upd<c1>(zero[idx] + SHIFT, 1), cond[idx] = GREATER;  // 零点在查询范围内，则保存到对应的树状数组中
      }

      else  // 当斜率 = 0 时，不等式恒成立或恒不成立
        (b > c) ? (++cnt, cond[++idx] = TRUE) : cond[++idx] = FALSE;
    }

    else if (type == "Del") {
      if (cond[a] == TRUE) --cnt;                                     // 原不等式在查询范围内恒成立
      else if (cond[a] == LESS) FWK.upd<c2>(zero[a] + SHIFT, -1);     // 原不等式的斜率 < 0
      else if (cond[a] == GREATER) FWK.upd<c1>(zero[a] + SHIFT, -1);  // 原不等式的斜率 > 0
      cond[a] = REMOVED;
    }

    else {
      // 斜率 > 0 的所有函数中，成立的是零点小于 k 的函数
      // 斜率 < 0 的所有函数中，成立的是零点大于 k 的函数
      int ans = FWK.sum<c1>(a - 1 + SHIFT) + FWK.sum<c2>(MAX_V) - FWK.sum<c2>(a + SHIFT);
      std::cout << ans + cnt << '\n';
    }
  }

  return 0;
}
