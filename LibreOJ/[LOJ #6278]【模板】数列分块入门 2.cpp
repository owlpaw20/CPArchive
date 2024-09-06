#include <bits/stdc++.h>

using LL = long long;

const int MAX_N = 5e4 + 5;
const int MAX_LEN = 250;

int N, len, b_cnt;
int bel[MAX_N];
LL h[MAX_N], t[MAX_N];

struct Block {
  int l, r;
  LL tag;

  void sort() {
    for (int i = l; i <= r; ++i) t[i] = h[i];
    std::sort(t + l, t + r + 1);
  }

  int get(LL x) { return std::lower_bound(t + l, t + r + 1, x - tag) - t - l; }

  Block() {}
  Block(int i) : l((i - 1) * len + 1), r(std::min(N, i * len)), tag(0) { sort(); }

} block[MAX_LEN];

void init() {
  b_cnt = N / len + bool(N % len);

  for (int i = 1; i <= N; ++i) bel[i] = (i - 1) / len + 1;
  for (int i = 1; i <= b_cnt; ++i) block[i] = Block(i);
}

void upd(int l, int r, LL x) {
  if (bel[l] == bel[r]) {
    for (int i = l; i <= r; ++i) h[i] += x;
    return block[bel[l]].sort();
  }

  for (int i = l; i <= block[bel[l]].r; ++i) h[i] += x;
  for (int i = r; i >= block[bel[r]].l; --i) h[i] += x;
  for (int i = bel[l] + 1; i < bel[r]; ++i) block[i].tag += x;
  block[bel[l]].sort(), block[bel[r]].sort();
}

int qry(int l, int r, LL x) {
  int ans = 0;

  if (bel[l] == bel[r]) {
    for (int i = l; i <= r; ++i) ans += (h[i] + block[bel[l]].tag < x);
    return ans;
  }

  for (int i = l; i <= block[bel[l]].r; ++i) ans += (h[i] + block[bel[l]].tag < x);
  for (int i = r; i >= block[bel[r]].l; --i) ans += (h[i] + block[bel[r]].tag < x);
  for (int i = bel[l] + 1; i < bel[r]; ++i) ans += block[i].get(x);
  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N, len = sqrt(N);
  for (int i = 1; i <= N; ++i) std::cin >> h[i];

  init();

  while (N--) {
    static int type, l, r, c;
    std::cin >> type >> l >> r >> c;

    if (type) std::cout << qry(l, r, (LL)c * c) << '\n';
    else upd(l, r, c);
  }

  std::cout.flush();
  return 0;
}
