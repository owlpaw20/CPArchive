#pragma GCC optimize("O2,unroll-loops,inline")
#include <bits/stdc++.h>

const int MAX_N = 3.5e4 + 5;
const int MAX_K = 55;

int N, K;
int a[MAX_N];
int lb[MAX_N], prev[MAX_N];

int f[MAX_N][MAX_K];  // f[i][j] 为将前 i 个蛋糕装进 j 个盒子的最大价值

struct SegT {
  struct Node {
    int val, tag;
  };

  std::vector<Node> tr;
  SegT() { tr.resize((N + 5) << 2); }

  void build(int box, int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return tr[u].val = f[nl - 1][box - 1], void();
    int mid = (nl + nr) >> 1;
    build(box, u << 1, nl, mid);
    build(box, u << 1 | 1, mid + 1, nr);
    tr[u].val = std::max(tr[u << 1].val, tr[u << 1 | 1].val);
  }

  void push(int u) {
    if (!tr[u].tag) return;
    tr[u << 1].val += tr[u].tag;
    tr[u << 1].tag += tr[u].tag;
    tr[u << 1 | 1].val += tr[u].tag;
    tr[u << 1 | 1].tag += tr[u].tag;
    tr[u].tag = 0;
  }

  void upd(int l, int r, int x, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u].val += x, tr[u].tag += x, void();
    push(u);
    int mid = (nl + nr) >> 1;
    if (l <= mid) upd(l, r, x, u << 1, nl, mid);
    if (r > mid) upd(l, r, x, u << 1 | 1, mid + 1, nr);
    tr[u].val = std::max(tr[u << 1].val, tr[u << 1 | 1].val);
  }

  int qry(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u].val;
    push(u);
    int mid = (nl + nr) >> 1, ret = 0;
    if (l <= mid) ret = std::max(ret, qry(l, r, u << 1, nl, mid));
    if (r > mid) ret = std::max(ret, qry(l, r, u << 1 | 1, mid + 1, nr));
    return ret;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> K;

  for (int i = 1; i <= N; ++i) {
    std::cin >> a[i];
    lb[i] = prev[a[i]] + 1;
    prev[a[i]] = i;
  }

  for (int i = 1; i <= K; ++i) {
    SegT T;
    T.build(i);
    for (int j = 1; j <= N; ++j) {
      T.upd(lb[j], j, 1);
      f[j][i] = T.qry(1, j);
    }
  }

  std::cout << f[N][K] << std::flush;
  return 0;
}
