#pragma GCC optimize("O2,unroll-loops")
#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 2e5 + 5;
const int MAX_V = 4e5;

int N, k;
int a[MAX_N];

struct SegT {
  struct Node {
    i64 cnt, tag;
    int len;
    inline void modify(i64 v) { cnt += len * v, tag += v; }
  } tr[(MAX_V + 5) << 2];

  inline void push(int u) {
    if (!tr[u].tag) return;
    tr[u << 1].modify(tr[u].tag);
    tr[u << 1 | 1].modify(tr[u].tag);
    tr[u].tag = 0;
  }

  void build(int u = 1, int nl = 0, int nr = MAX_V) {
    tr[u].tag = 0, tr[u].len = nr - nl + 1;
    if (nl == nr) return tr[u].cnt = !nl, void();
    int mid = (nl + nr) >> 1;
    build(u << 1, nl, mid);
    build(u << 1 | 1, mid + 1, nr);
    tr[u].cnt = tr[u << 1].cnt + tr[u << 1 | 1].cnt;
  }

  void upd(int l, int r, i64 v, int u = 1, int nl = 0, int nr = MAX_V) {
    if (nl >= l && nr <= r) return tr[u].modify(v);
    push(u);
    int mid = (nl + nr) >> 1;
    if (l <= mid) upd(l, r, v, u << 1, nl, mid);
    if (r > mid) upd(l, r, v, u << 1 | 1, mid + 1, nr);
    tr[u].cnt = tr[u << 1].cnt + tr[u << 1 | 1].cnt;
  }

  int bin1(int u = 1, int nl = 0, int nr = MAX_V) {
    if (nl == nr) return nl;
    int mid = (nl + nr) >> 1;
    push(u);
    if (tr[u << 1].cnt) return bin1(u << 1, nl, mid);
    else return bin1(u << 1 | 1, mid + 1, nr);
  }

  int bin2(i64 k, int u = 1, int nl = 0, int nr = MAX_V) {
    if (nl == nr) return nl;
    int mid = (nl + nr) >> 1;
    push(u);
    if (tr[u << 1].cnt >= k) return bin2(k, u << 1, nl, mid);
    else return bin2(k - tr[u << 1].cnt, u << 1 | 1, mid + 1, nr);
  }
} T;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> k;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  T.build();
  std::sort(a + 1, a + N + 1, std::greater<>());

  i64 white_cnt = 1;
  i64 ans = std::numeric_limits<i64>::max();

  for (int i = 1; i <= N; ++i) {
    int min_pos = T.bin1();
    T.upd(min_pos, min_pos, -1), --white_cnt;
    T.upd(min_pos + 2, min_pos + 1 + (a[i] - 1) / 2, 1);
    T.upd(min_pos + 2, min_pos + a[i] - (a[i] - 1) / 2, 1);
    if ((white_cnt += a[i] - 1) >= k) ans = std::min(ans, (i64)T.bin2(k));
  }

  std::cout << (ans == std::numeric_limits<i64>::max() ? -1 : ans) << '\n';
  return 0;
}
