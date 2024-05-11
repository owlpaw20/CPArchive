#pragma GCC optimize("O2,unroll-loops,inline")

#include <cmath>
#include <iostream>
#include <algorithm>

using l64 = long long;

const int MAX_N = 2e5 + 5;
const int MAX_Q = 2e5 + 5;
const int MAX_V = 1e6 + 5;

int N, Q, a[MAX_N], bel[MAX_N];
l64 ans[MAX_Q], cnt[MAX_V], sum;

struct Query {
  int l, r, id;
  bool operator<(const Query& t) const {
    if (bel[l] != bel[t.l]) return bel[l] < bel[t.l];
    return r < t.r;
  }
} q[MAX_Q];

void expand(int x) {
  sum += cnt[a[x]] * a[x] * 2 + a[x];
  ++cnt[a[x]];
}

void shrink(int x) {
  sum -= cnt[a[x]] * a[x] * 2 - a[x];
  --cnt[a[x]];
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> Q;

  int block = sqrt(N);
  for (int i = 1; i <= N; ++i)
    std::cin >> a[i], bel[i] = i / block;

  for (int i = 1; i <= Q; ++i)
    std::cin >> q[i].l >> q[i].r, q[i].id = i;

  std::sort(q + 1, q + Q + 1);

  for (int i = 1, l = 1, r = 0; i <= Q; ++i) {
    while (l > q[i].l) expand(--l);
    while (r < q[i].r) expand(++r);
    while (l < q[i].l) shrink(l++);
    while (r > q[i].r) shrink(r--);
    ans[q[i].id] = sum;
  }

  for (int i = 1; i <= Q; ++i) std::cout << ans[i] << '\n';
  return std::cout << std::endl, 0;
}
