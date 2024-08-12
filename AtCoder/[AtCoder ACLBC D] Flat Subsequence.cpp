#include <bits/stdc++.h>

const int MAX_N = 3e5 + 5;
const int MAX_V = 6e5;

int N, K;

struct SegmentTree {
  int max[MAX_N << 3];

  void set(int x, int val, int u = 1, int nl = 0, int nr = MAX_V) {
    if (nl == nr) return max[u] = val, void();
    int mid = (nl + nr) >> 1;
    if (x <= mid) set(x, val, u << 1, nl, mid);
    else set(x, val, u << 1 | 1, mid + 1, nr);
    max[u] = std::max(max[u << 1], max[u << 1 | 1]);
  }

  int qry(int l, int r, int u = 1, int nl = 0, int nr = MAX_V) {
    if (nl >= l && nr <= r) return max[u];
    int mid = (nl + nr) >> 1, mx = 0;
    if (l <= mid) mx = std::max(mx, qry(l, r, u << 1, nl, mid));
    if (r > mid) mx = std::max(mx, qry(l, r, u << 1 | 1, mid + 1, nr));
    return mx;
  }
} F;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> K;

  for (int i = 1, a; i <= N; ++i) {
    std::cin >> a;
    F.set(a, F.qry(std::max(0, a - K), a + K) + 1);
  }

  std::cout << F.max[1] << std::flush;
  return 0;
}
