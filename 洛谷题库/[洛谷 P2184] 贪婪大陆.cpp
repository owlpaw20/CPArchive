#include <bits/stdc++.h>

const int MAX_N = 1e5 + 5;

int N, M;

struct BIT {
  int c[MAX_N];

  void upd(int x, int val = 1) {
    for (; x <= N; x += x & -x)
      c[x] += val;
  }

  int qry(int x) {
    int sum = 0;
    for (; x; x -= x & -x) sum += c[x];
    return sum;
  }
} tS, tT;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  while (M--) {
    static int type, l, r;
    std::cin >> type >> l >> r;

    if (type == 1) tS.upd(l), tT.upd(r);
    else std::cout << tS.qry(r) - tT.qry(l - 1) << '\n';
  }

  std::cout.flush();
  return 0;
}
