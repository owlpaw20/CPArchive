#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

const int MAX_N = 5e5 + 5;

int N;
int a[MAX_N], b[MAX_N];
int root[MAX_N];

struct PerSegT {
  struct Node {
    int l, r;
    int cnt;
  } t[MAX_N << 5];

  int size;

  int build(int l, int r) {
    int u = ++size;
    if (l == r) return u;
    int mid = (l + r) >> 1;
    t[u].l = build(l, mid);
    t[u].r = build(mid + 1, r);
    return u;
  }

  int insert(int u, int l, int r, int x) {
    int v = ++size;
    t[v] = t[u];
    if (l == r) return ++t[v].cnt, v;

    int mid = (l + r) >> 1;
    if (x <= mid) t[v].l = insert(t[u].l, l, mid, x);
    else t[v].r = insert(t[u].r, mid + 1, r, x);

    t[v].cnt = t[t[v].l].cnt + t[t[v].r].cnt;
    return v;
  }

  int query(int u, int v, int l, int r, int k) {
    if (l == r) return l;
    int L = t[t[v].l].cnt - t[t[u].l].cnt;
    int R = t[t[v].r].cnt - t[t[u].r].cnt;
    int mid = (l + r) >> 1;
    if (L > k) return query(t[u].l, t[v].l, l, mid, k);
    if (R > k) return query(t[u].r, t[v].r, mid + 1, r, k);
    return 0;
  }

  PerSegT() : size(0) {}
} PST;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int Q;
  std::cin >> N >> Q;

  for (int i = 1; i <= N; ++i) std::cin >> a[i];
  memcpy(b, a, sizeof(int) * (N + 2));

  std::sort(b + 1, b + N + 1);
  int M = std::unique(b + 1, b + N + 1) - b - 1;
  root[0] = PST.build(1, M);

  for (int i = 1, x; i <= N; ++i) {
    x = std::lower_bound(b + 1, b + M + 1, a[i]) - b;
    root[i] = PST.insert(root[i - 1], 1, M, x);
  }

  while (Q--) {
    static int L, R;
    std::cin >> L >> R;
    std::cout << b[PST.query(root[L - 1], root[R], 1, M, (R - L + 1) >> 1)] << '\n';
  }

  std::cout.flush();
  return 0;
}
