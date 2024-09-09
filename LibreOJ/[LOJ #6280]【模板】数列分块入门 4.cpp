#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 5e4 + 5;
const int MAX_B = 250;

int N, b_len, b_cnt, bel[MAX_N];
i64 a[MAX_N];

struct Block {
  int l, r;
  i64 sum, tag;

  Block() {}
  Block(int i)
      : l((i - 1) * b_len + 1), r(std::min(N, i * b_len)),
        sum(std::accumulate(a + l, a + r + 1, 0LL)), tag(0) {}

} b[MAX_B];

void init() {
  b_cnt = N / b_len + bool(N % b_len);
  for (int i = 1; i <= N; ++i) bel[i] = (i - 1) / b_len + 1;
  for (int i = 1; i <= b_cnt; ++i) b[i] = Block(i);
}

void upd(int l, int r, int x) {
  if (bel[l] == bel[r]) {
    b[bel[l]].sum += (r - l + 1LL) * x;
    for (int i = l; i <= r; ++i) a[i] += x;
    return;
  }

  for (int i = l; i <= b[bel[l]].r; ++i) a[i] += x;
  for (int i = r; i >= b[bel[r]].l; --i) a[i] += x;
  b[bel[l]].sum += (b[bel[l]].r - l + 1LL) * x;
  b[bel[r]].sum += (r - b[bel[r]].l + 1LL) * x;

  for (int i = bel[l] + 1; i < bel[r]; ++i) {
    b[i].sum += (b[i].r - b[i].l + 1LL) * x;
    b[i].tag += x;
  }
}

i64 qry(int l, int r) {
  i64 sum = 0;

  if (bel[l] == bel[r]) {
    for (int i = l; i <= r; ++i) sum += a[i];
    return sum + (r - l + 1LL) * b[bel[l]].tag;
  }

  for (int i = l; i <= b[bel[l]].r; ++i) sum += a[i];
  for (int i = r; i >= b[bel[r]].l; --i) sum += a[i];
  sum += (b[bel[l]].r - l + 1LL) * b[bel[l]].tag;
  sum += (r - b[bel[r]].l + 1LL) * b[bel[r]].tag;

  for (int i = bel[l] + 1; i < bel[r]; ++i) sum += b[i].sum;
  return sum;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N, b_len = sqrt(N);
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  init();

  while (N--) {
    static int type, l, r, c;
    std::cin >> type >> l >> r >> c;

    if (!type) upd(l, r, c);
    else std::cout << qry(l, r) % (c + 1) << '\n';
  }

  std::cout.flush();
  return 0;
}
