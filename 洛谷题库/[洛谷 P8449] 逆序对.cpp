#include <bits/stdc++.h>

const int MAX_N = 2e5 + 5;
const int MAX_V = 2e6;

int N;

struct BinIdxTree {
  int c[MAX_V + 5];

  void upd(int x, int v) {
    while (x <= MAX_V)
      c[x] += v, x += (x & -x);
  }

  int qry(int x) {
    int sum = 0;
    while (x) sum += c[x], x -= (x & -x);
    return sum;
  }

  int qry(int l, int r) { return qry(r) - qry(l - 1); }
} T;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  std::cin >> N >> q;

  bool ans = false;

  for (int i = 1, x; i <= N; ++i) {
    std::cin >> x;
    ans ^= T.qry(x + 1, MAX_V) % 2, T.upd(x, 1);
  }

  auto swap_subseq = [](int l1, int r1, int l2, int r2) -> bool {
    static int len1, len2, len3;
    len1 = r1 - l1 + 1;
    len2 = r2 - l2 + 1;
    len3 = l2 - r1 - 1;
    return (len1 * len2 + len2 * len3 + len1 * len3) % 2;
  };

  while (q--) {
    static int type, l1, r1, l2, r2, k;
    std::cin >> type;

    switch (type) {
      case 1:
        std::cin >> l1 >> r1 >> l2 >> r2;
        ans ^= swap_subseq(l1, r1, l2, r2);
        break;

      case 2:
        std::cin >> l1 >> r1 >> k;
        ans ^= swap_subseq(l1, r1, r1 + 1, k);
        break;

      case 3:
        std::cin >> k;
        ans ^= T.qry(k + 1, MAX_V) % 2;
        T.upd(k, 1);
        break;

      case 4:
        std::cin >> k;
        ans ^= T.qry(k) % 2;
        T.upd(k, 1);
        break;

      default: break;
    }

    std::cout << (ans ? "odd\n" : "even\n");
  }

  std::cout.flush();
  return 0;
}
