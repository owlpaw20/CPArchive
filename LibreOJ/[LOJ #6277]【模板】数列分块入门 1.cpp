#include <bits/stdc++.h>

using LL = long long;

const int MAX_N = 5e4 + 5;
const int MAX_LEN = 250;

int N, len;
LL a[MAX_N], tag[MAX_LEN];

void upd(int l, int r, LL x) {
  if (l / len == r / len) {
    for (int i = l; i <= r; ++i) a[i] += x;
    return;
  }

  int i = l, j = r;
  while (i / len == l / len) a[i] += x, ++i;
  while (j / len == r / len) a[j] += x, --j;
  for (int k = i / len; k <= j / len; ++k) tag[k] += x;
}

LL qry(int x) { return a[x] + tag[x / len]; }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N, len = sqrt(N);
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  while (N--) {
    static int type, l, r, c;
    std::cin >> type >> l >> r >> c;

    if (!type) upd(l, r, c);
    else std::cout << qry(r) << '\n';
  }

  std::cout.flush();
  return 0;
}
