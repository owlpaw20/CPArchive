#include <tuple>
#include <iostream>
#include <algorithm>

#define endl '\n'

using std::cin;
using std::cout;
using std::get;

namespace FastIO {
  const int MAX_BUF = 1 << 20;
  char buf[MAX_BUF], *p1, *p2;

#define getchar() \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)

  int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
  }
  void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
  }
}  // namespace FastIO
using namespace FastIO;

using i64 = long long;
using TUP = std::tuple<int, int, int>;

const int MAX_N = 1e6 + 5;

int N, M;
int a[MAX_N], vis[MAX_N];
TUP qry[MAX_N];
int res[MAX_N];

struct Fenwick {
  int data[MAX_N];

  void inc(int x, int v) {
    for (; x <= N; x += (x & -x))
      data[x] += v;
  }

  i64 sum(int x) {
    i64 sum = 0;
    for (; x; x -= (x & -x))
      sum += data[x];
    return sum;
  }
} FWK;

int main() {
  N = read();
  for (int i = 1; i <= N; ++i) a[i] = read();

  M = read();
  for (int i = 1; i <= M; ++i)
    qry[i] = {read(), read(), i};

  auto cmp = [&](TUP x, TUP y) {
    return get<1>(x) < get<1>(y);
  };
  std::sort(qry + 1, qry + M + 1, cmp);

  for (int i = 1, nx = 1; i <= M; ++i) {
    auto [l, r, idx] = qry[i];
    for (int j = nx; j <= r; ++j) {
      if (vis[a[j]]) FWK.inc(vis[a[j]], -1);
      FWK.inc(j, 1);
      vis[a[j]] = j;
    }
    nx = r + 1;
    res[idx] = FWK.sum(r) - FWK.sum(l - 1);
  }

  for (int i = 1; i <= M; ++i)
    cout << res[i] << endl;

  return fflush(stdout), 0;
}
