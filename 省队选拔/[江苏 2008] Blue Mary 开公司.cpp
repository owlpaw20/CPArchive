#include <cmath>
#include <string>
#include <iostream>

#define endl '\n'

#ifdef _WIN32
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#endif

#ifdef unix
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

namespace FastIO {
  template <typename T>
  inline T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
  }

  template <typename T>
  inline void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
  }
}  // namespace FastIO
using namespace FastIO;

namespace FastStrIO {
  inline std::string read() {
    std::string ret;
    char ch = getchar();
    while (ch == ' ' || ch == '\n' || ch == '\r') ch = getchar();
    while (ch != ' ' && ch != '\n' && ch != '\r') ret += ch, ch = getchar();
    return ret;
  }
}  // namespace FastStrIO
using namespace FastStrIO;

namespace FastFloatIO {
  template <typename T>
  inline T fread() {
    T x = 0.0;
    int f = 1;
    char ch = getchar();
    while ((ch < '0' || ch > '9') && ch != '.') {
      if (ch == '-') f = -f;
      ch = getchar();
    }

    while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    if (ch != '.') return x * f;

    T y = 1;
    ch = getchar();
    while (ch >= '0' && ch <= '9') x += (ch - 48) * (y *= 0.1), ch = getchar();
    return x * f;
  }
}  // namespace FastFloatIO
using namespace FastFloatIO;

using f64 = double;
using c32 = const int;

const int MAX_N = 1e5 + 5;
const int MAX_V = 5e4;
const int MAX_V_SZ = MAX_V + 5;
const f64 INF = 2e9;
const f64 EPS = 1e-10;

template <typename T>
inline int fcmp(const T x, const T y) {
  if (fabsl(x - y) < EPS) return 0;
  return x > y ? 1 : -1;
}

int idx;

struct LinearFunction {
  f64 k, b;
  inline f64 operator()(const int x) { return k * (x - 1) + b; }
} f[MAX_N];

struct LiChaoTree {
  int dom[MAX_V_SZ << 2];

  void insert(int i, c32 u = 1, c32 nl = 1, c32 nr = MAX_V) {
    if (!dom[u]) return dom[u] = i, void();

    c32 mid = (nl + nr) >> 1;

    if (fcmp(f[i](mid), f[dom[u]](mid)) == 1) std::swap(i, dom[u]);

    if (fcmp(f[i](nl), f[dom[u]](nl)) + (i < dom[u]) >= 1) insert(i, u << 1, nl, mid);
    if (fcmp(f[i](nr), f[dom[u]](nr)) + (i < dom[u]) >= 1) insert(i, u << 1 | 1, mid + 1, nr);
  }

  f64 query(c32 x, c32 u = 1, c32 nl = 1, c32 nr = MAX_V) {
    f64 ret = (dom[u] ? f[dom[u]](x) : 0);

    if (nl == nr) return ret;

    c32 mid = (nl + nr) >> 1;

    if (x <= mid) ret = std::max(ret, query(x, u << 1, nl, mid));
    else ret = std::max(ret, query(x, u << 1 | 1, mid + 1, nr));

    return ret;
  }

} LCT;

int main() {
  int Q = read<int>();

  while (Q--) {
    std::string type = read();
    if (type.front() == 'P') {
      f64 b = fread<f64>(), k = fread<f64>();
      f[++idx] = {k, b};
      LCT.insert(idx);
    } else
      FastIO::write(int(LCT.query(read<int>()) / 100)), putchar('\n');
  }

  return fflush(stdout), 0;
}
