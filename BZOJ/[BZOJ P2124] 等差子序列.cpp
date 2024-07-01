#include <cstring>
#include <iostream>

namespace FastIO {
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2;
  char pbuf[MAX_BUF], *pp = pbuf;

  char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }
  void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  void flush() { (pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout); }

  template <typename T>
  T read() {
    short int f = 1;
    T var = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9') var = var * 10 + ch - '0', ch = getchar();
    return var * f;
  }
}  // namespace FastIO
using namespace FastIO;

using LL = long long;

const int MAX_N = 5e5 + 5;
const int BASE = 1131113;
const int MOD = 1311313331;

int N;
int p_B[MAX_N];

void prep() {
  p_B[0] = 1;
  for (int i = 1; i <= (int)5e5; ++i)
    p_B[i] = (LL)p_B[i - 1] * BASE % MOD;
}

struct SegT {
  struct Node {
    int hash, r_hash;
  } t[MAX_N << 2];

#define L(x) ((x) << 1)
#define R(x) ((x) << 1 | 1)

  void pull(int u, int l, int r) {
    int mid = (l + r) >> 1;
    t[u].hash = ((LL)t[L(u)].hash * p_B[r - mid] + t[R(u)].hash) % MOD;
    t[u].r_hash = ((LL)t[R(u)].r_hash * p_B[mid - l + 1] + t[L(u)].r_hash) % MOD;
  }

  void update(int pos, int val, int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return t[u].hash = t[u].r_hash = val, void();
    int mid = (nl + nr) >> 1;
    if (pos <= mid) update(pos, val, L(u), nl, mid);
    else update(pos, val, R(u), mid + 1, nr);
    pull(u, nl, nr);
  }

  int hash(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return t[u].hash;
    int mid = (nl + nr) >> 1;
    if (l > mid) return hash(l, r, R(u), mid + 1, nr);
    if (r <= mid) return hash(l, r, L(u), nl, mid);
    return ((LL)hash(l, r, L(u), nl, mid) * p_B[std::min(nr, r) - mid] + hash(l, r, R(u), mid + 1, nr)) % MOD;
  }

  int r_hash(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return t[u].r_hash;
    int mid = (nl + nr) >> 1;
    if (l > mid) return r_hash(l, r, R(u), mid + 1, nr);
    if (r <= mid) return r_hash(l, r, L(u), nl, mid);
    return ((LL)r_hash(l, r, R(u), mid + 1, nr) * p_B[mid - std::max(nl, l) + 1] + r_hash(l, r, L(u), nl, mid)) % MOD;
  }

#undef L
#undef R
} T;

void solve() {
  N = read<int>();

  memset(&T.t, 0, sizeof(SegT::Node) * ((N << 2) + 1));

  bool success = false;

  for (int i = 1, x; i <= N; ++i) {
    x = read<int>();
    if (success) continue;

    T.update(x, 1);
    int intvl = std::min(N - x, x - 1);
    if (T.hash(x, x + intvl) != T.r_hash(x - intvl, x)) putchar('Y'), success = true;
  }

  if (!success) putchar('N');
  putchar('\n');
}

int main() {
  prep();

  int T = read<int>();
  while (T--) solve();

  return flush(), 0;
}
