#include <bits/stdc++.h>

const int MAX_M = 1e5 + 10;

using u32 = unsigned int;
using PII = std::pair<int, int>;
using cRefStr = const std::string &;

int N, M;
std::string str;

PII get(cRefStr s) {
  int val_0 = 0, val_1 = 0;

  for (int i = 0; i < N; ++i)
    if (s[i] == '0') val_0 |= 1 << i;       // 用 val_0 存储该字符串指定必须为 0 的位
    else if (s[i] == '1') val_1 |= 1 << i;  // 用 val_1 存储该字符串指定必须为 1 的位

  return PII(val_0, val_1);
}

// 线段树维护所有字符串的 val_0 与 val_1 的区间按位或和
struct SegT {
  struct Node {
    int zero, one;
  } tr[MAX_M << 2];

  using cRefNode = const Node &;

  Node merge(cRefNode L, cRefNode R) { return (Node){L.zero | R.zero, L.one | R.one}; }

  void build(int u = 1, int nl = 1, int nr = M) {
    if (nl == nr) {
      std::cin >> str;
      PII tmp = get(str);
      tr[u].zero = tmp.first;
      tr[u].one = tmp.second;
      return;
    }

    int mid = (nl + nr) >> 1;
    build(u << 1, nl, mid);
    build(u << 1 | 1, mid + 1, nr);
    tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
  }

  void upd(int x, cRefStr s, int u = 1, int nl = 1, int nr = M) {
    if (nl == nr) {
      PII tmp = get(s);
      tr[u].zero = tmp.first;
      tr[u].one = tmp.second;
      return;
    }

    int mid = (nl + nr) >> 1;
    if (x <= mid) upd(x, s, u << 1, nl, mid);
    else upd(x, s, u << 1 | 1, mid + 1, nr);
    tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
  }

  Node qry(int l, int r, int u = 1, int nl = 1, int nr = M) {
    if (nl >= l && nr <= r) return tr[u];
    int mid = (nl + nr) >> 1;
    if (r <= mid) return qry(l, r, u << 1, nl, mid);
    if (l > mid) return qry(l, r, u << 1 | 1, mid + 1, nr);
    return merge(qry(l, r, u << 1, nl, mid), qry(l, r, u << 1 | 1, mid + 1, nr));
  }
} T;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  std::cin >> N >> M >> q;
  const int mask = (1 << N) - 1;

  T.build();

  int ans = 0;

  while (q--) {
    static int type, l, r, t;
    std::cin >> type;

    if (!type) {
      std::cin >> l >> r;
      auto [or_0, or_1] = T.qry(l, r);

      if (!(or_0 & or_1)) {                       // 如果必须为 0 的位与必须为 1 的位没有冲突
        u32 undetermined = ~or_0 & ~or_1 & mask;  // 计算通过字符串无法确定的二进制位有多少个
        ans ^= 1 << std::popcount(undetermined);  // 则答案为 2 ^ (不确定的二进制位的数量)
      }
    }

    else {
      std::cin >> t >> str;
      T.upd(t, str);
    }
  }

  std::cout << ans << std::flush;
  return 0;
}
