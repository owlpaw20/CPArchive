#include <bits/stdc++.h>

using f128 = long double;

const int DAYS = 182376;
const int MAX_N = DAYS + 5;

f128 M;
int N, k;
int w[MAX_N];

int p[MAX_N], cnt, a[MAX_N];
bool np[MAX_N];

void sieve(int lim) {
  np[0] = np[1] = true;

  for (int i = 2; i <= lim; ++i) {
    if (!np[i]) p[++cnt] = i, a[i] = i;

    for (int j = 1; j <= cnt && i * p[j] <= lim; ++j) {
      np[i * p[j]] = true;
      if (i % p[j]) a[i * p[j]] = a[i] + p[j];
      else a[i * p[j]] = a[i], j = cnt + 1;
    }
  }
}

int cmp(f128 x, f128 y) {
  if (fabsl(x - y) <= std::numeric_limits<f128>::epsilon()) return 0;
  return x > y ? 1 : -1;
}

struct LinearFunction {
  f128 k, b;
  f128 operator()(f128 x) { return k * x + b; }
} f[MAX_N];

struct LiChaoTree {
  int dom[MAX_N << 2];

  void ins(int x, int u = 1, int nl = 0, int nr = DAYS) {
    int mid = (nl + nr) >> 1;
    if (!dom[u]) return dom[u] = x, void();
    if (cmp(f[x](mid), f[dom[u]](mid)) == -1) std::swap(dom[u], x);
    if (cmp(f[dom[u]](nl), f[x](nl)) == 1) ins(x, u << 1, nl, mid);
    if (cmp(f[dom[u]](nr), f[x](nr)) == 1) ins(x, u << 1 | 1, mid + 1, nr);
  }

  f128 qry(int x, int u = 1, int nl = 0, int nr = DAYS) {
    f128 ret = dom[u] ? f[dom[u]](x) : std::numeric_limits<f128>::max();
    if (nl == nr) return ret;
    int mid = (nl + nr) >> 1;
    if (x <= mid) return std::min(ret, qry(x, u << 1, nl, mid));
    return std::min(ret, qry(x, u << 1 | 1, mid + 1, nr));
  }
} LCT;

int main() {
  std::fixed(std::cout).precision(10);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M >> k;
  for (int i = 1; i <= N; ++i) std::cin >> w[i];
  sieve(*std::max_element(w + 1, w + N + 1));

  f[1] = LinearFunction(1.0 / M, (f128)a[w[1]] / M);
  LCT.ins(1);

  f128 ans = M;

  for (int i = 2; i <= N; ++i) {
    M = 1.0 / LCT.qry(a[w[i]]) + k, ans += M;
    f[i] = LinearFunction(1.0 / M, (f128)a[w[i]] / M);
    LCT.ins(i);
  }

  std::cout << ans << std::flush;
  return 0;
}
