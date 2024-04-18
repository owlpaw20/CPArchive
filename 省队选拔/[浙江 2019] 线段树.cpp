#include <cstdint>
#include <iostream>

#define endl '\n'

using c32 = const int32_t;
using u32 = uint32_t;

const int MAX_N = 1e5 + 5;
const int MOD = 998244353;

int N, M, p = 1;

inline int add(int x, c32 y) {
  x += y;
  return (x < MOD) ? (x) : (x - MOD);
}
inline int sub(int x, c32 y) {
  x -= y;
  return (x < 0) ? (x + MOD) : (x);
}

struct SegmentTree {
  struct TreeNode {
    int f, g;
    int f_tag, g_tag;
    int f_sum;

    void modify_f_tag(int tag) {
      f = (int64_t)f * tag % MOD;
      f_tag = (int64_t)f_tag * tag % MOD;
      f_sum = (int64_t)f_sum * tag % MOD;
    }

    void modify_g_tag(int tag) {
      g = (int64_t)g * tag % MOD;
      g_tag = (int64_t)g_tag * tag % MOD;
    }

    void pull(const TreeNode x, const TreeNode y) { f_sum = add(f, add(x.f_sum, y.f_sum)); }

    void push(TreeNode &x, TreeNode &y) {
      if (f_tag != 1) x.modify_f_tag(f_tag), y.modify_f_tag(f_tag), f_tag = 1;
      if (g_tag != 1) x.modify_g_tag(g_tag), y.modify_g_tag(g_tag), g_tag = 1;
    }
  } node[MAX_N << 3];

  void build(c32 u = 1, c32 nl = 1, c32 nr = N) {
    node[u].g = node[u].f_tag = node[u].g_tag = 1;

    if (nl == nr) return;

    int mid = (nl + nr) >> 1;

    build(u << 1, nl, mid);
    build(u << 1 | 1, mid + 1, nr);
  }

  void update(c32 l, c32 r, c32 u = 1, c32 nl = 1, c32 nr = N) {
    node[u].push(node[u << 1], node[u << 1 | 1]);

    if (nl == l && nr == r) {
      node[u].f = add(node[u].f, p);
      node[u << 1].modify_f_tag(2);
      node[u << 1 | 1].modify_f_tag(2);
      node[u].pull(node[u << 1], node[u << 1 | 1]);
      return;
    }

    int mid = (nl + nr) >> 1;
    node[u].g = add(node[u].g, p);

#define ul (u << 1)
#define ur (u << 1 | 1)
    if (r <= mid) {
      update(l, r, ul, nl, mid);
      node[ur].push(node[ur << 1], node[ur << 1 | 1]);
      node[ur].f = add(node[ur].f, sub(p, node[ur].g));
      node[ur].g = add(node[ur].g, node[ur].g);
      node[ur << 1].modify_f_tag(2), node[ur << 1 | 1].modify_f_tag(2);
      node[ur << 1].modify_g_tag(2), node[ur << 1 | 1].modify_g_tag(2);
      node[ur].pull(node[ur << 1], node[ur << 1 | 1]);
    } else if (l > mid) {
      update(l, r, ur, mid + 1, nr);
      node[ul].push(node[ul << 1], node[ul << 1 | 1]);
      node[ul].f = add(node[ul].f, sub(p, node[ul].g));
      node[ul].g = add(node[ul].g, node[ul].g);
      node[ul << 1].modify_f_tag(2), node[ul << 1 | 1].modify_f_tag(2);
      node[ul << 1].modify_g_tag(2), node[ul << 1 | 1].modify_g_tag(2);
      node[ul].pull(node[ul << 1], node[ul << 1 | 1]);
    } else {
      update(l, mid, ul, nl, mid);
      update(mid + 1, r, ur, mid + 1, nr);
    }
#undef ul
#undef ur

    node[u].pull(node[u << 1], node[u << 1 | 1]);
  }

} SGT;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  SGT.build();

  while (M--) {
    int o, l, r;
    std::cin >> o;

    if (o == 1) {
      std::cin >> l >> r;
      SGT.update(l, r);
      p = add(p, p);
    } else
      std::cout << SGT.node[1].f_sum << endl;
  }

  return fflush(stdout), 0;
}
