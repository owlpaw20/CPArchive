#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 1e5 + 5;
const int MAX_B = 4e2 + 5;

int N;

int b_len, b_cnt;
int bel[MAX_N];
i64 t[MAX_N];

struct Block {
  int l, r;
  i64 tag;
  std::set<i64> set;

  bool sort() { return set = std::set<i64>(t + l, t + r + 1), false; }

  i64 get(i64 x) {
    auto pre_iter = set.lower_bound(x - tag);
    return pre_iter == set.begin() ? -1 : *--pre_iter + tag;
  }

  Block() {}
  Block(int i) : l((i - 1) * b_len + 1), r(std::min(N, i * b_len)), tag(0) { sort(); }

} block[MAX_B];

void init() {
  b_cnt = N / b_len + bool(N % b_len);
  for (int i = 1; i <= N; ++i) bel[i] = (i - 1) / b_len + 1;
  for (int i = 1; i <= b_cnt; ++i) block[i] = Block(i);
}

void upd(int l, int r, i64 x) {
  if (bel[l] == bel[r]) {
    for (int i = l; i <= r; ++i) t[i] += x;
    return block[bel[l]].sort(), void();
  }

  for (int i = l; i <= block[bel[l]].r || block[bel[l]].sort(); ++i) t[i] += x;
  for (int i = r; i >= block[bel[r]].l || block[bel[r]].sort(); --i) t[i] += x;
  for (int i = bel[l] + 1; i < bel[r]; ++i) block[i].tag += x;
}

i64 qry(int l, int r, i64 x) {
  i64 pre = -1, tag, tt;

  if (bel[l] == bel[r]) {
    tag = block[bel[l]].tag;

    for (int i = l; i <= r; ++i)
      ((tt = t[i] + tag) < x && tt > pre) && (pre = t[i] + tag);

    return pre;
  }

  tag = block[bel[l]].tag;
  for (int i = l; i <= block[bel[l]].r; ++i)
    ((tt = t[i] + tag) < x && tt > pre) && (pre = tt);

  tag = block[bel[r]].tag;
  for (int i = r; i >= block[bel[r]].l; --i)
    ((tt = t[i] + tag) < x && tt > pre) && (pre = tt);

  for (int i = bel[l] + 1; i < bel[r]; ++i)
    pre = std::max(pre, block[i].get(x));

  return pre;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N, b_len = sqrt(N);
  for (int i = 1; i <= N; ++i) std::cin >> t[i];

  init();

  while (N--) {
    static int type, l, r, x;
    std::cin >> type >> l >> r >> x;

    if (type) std::cout << qry(l, r, x) << '\n';
    else upd(l, r, x);
  }

  std::cout.flush();
  return 0;
}
