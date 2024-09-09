#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 5e4 + 5;
const int MAX_B = 250;

int N, b_len, b_cnt, bel[MAX_N];
int a[MAX_N];

struct Block {
  int l, r;
  i64 sum;
  bool is_fixed;

  bool postproc() {
    is_fixed = true;
    for (int i = l; i <= r && (a[i] < 2 || (is_fixed = false)); ++i);
    sum = std::accumulate(a + l, a + r + 1, 0LL);
    return false;
  }

  Block() {}
  Block(int i)
      : l((i - 1) * b_len + 1), r(std::min(N, i * b_len)),
        sum(0), is_fixed(false) { postproc(); }

} b[MAX_B];

void init() {
  b_len = sqrt(N);
  b_cnt = N / b_len + bool(N % b_len);
  for (int i = 1; i <= N; ++i) bel[i] = (i - 1) / b_len + 1;
  for (int i = 1; i <= b_cnt; ++i) b[i] = Block(i);
}

void upd(int l, int r) {
  if (bel[l] == bel[r]) {
    if (!b[bel[l]].is_fixed)
      for (int i = l; i <= r || b[bel[l]].postproc(); ++i)
        a[i] = sqrt(a[i]);
    return;
  }

  if (!b[bel[l]].is_fixed)
    for (int i = l; i <= b[bel[l]].r || b[bel[l]].postproc(); ++i)
      a[i] = sqrt(a[i]);

  if (!b[bel[r]].is_fixed)
    for (int i = r; i >= b[bel[r]].l || b[bel[r]].postproc(); --i)
      a[i] = sqrt(a[i]);

  for (int i = bel[l] + 1; i < bel[r]; ++i)
    if (!b[i].is_fixed)
      for (int j = b[i].l; j <= b[i].r || b[i].postproc(); ++j)
        a[j] = sqrt(a[j]);
}

i64 qry(int l, int r) {
  i64 sum = 0;

  if (bel[l] == bel[r]) {
    for (int i = l; i <= r; ++i) sum += a[i];
    return sum;
  }

  for (int i = l; i <= b[bel[l]].r; ++i) sum += a[i];
  for (int i = r; i >= b[bel[r]].l; --i) sum += a[i];
  for (int i = bel[l] + 1; i < bel[r]; ++i) sum += b[i].sum;

  return sum;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  init();

  while (N--) {
    static int type, l, r, c;
    std::cin >> type >> l >> r >> c;

    if (!type) upd(l, r);
    else std::cout << qry(l, r) << '\n';
  }

  std::cout.flush();
  return 0;
}
