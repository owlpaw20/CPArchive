#include <queue>
#include <cstdint>
#include <iostream>

namespace FastIO {
  const int MAX_BUF = 1 << 20;
  char buf[MAX_BUF], *p1, *p2;

#define getchar() \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)

  template <typename T>
  T read() {
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
  void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
  }
}  // namespace FastIO
using namespace FastIO;

using std::priority_queue;

using u32 = uint32_t;
using u64 = uint64_t;
using PII = std::pair<u64, u32>;

const u32 MAX_N = 5e5 + 10;

struct TRIE {
  u64 t[32 * MAX_N][2];
  u32 cnt[32 * MAX_N], idx;

  void insert(const u64 x) {
    for (int i = 31, p = 0; i >= 0; --i) {
      u64 c = (x >> i) & 1;
      if (!t[p][c]) t[p][c] = ++idx;
      p = t[p][c];
      cnt[p]++;
    }
  }

  u64 find(const u64 x, u32 rank) {
    u64 res = 0;
    for (int i = 31, p = 0; i >= 0; --i) {
      u32 c = (x >> i) & 1;
      if (!t[p][!c])
        p = t[p][c];
      else if (rank <= cnt[t[p][!c]])  // 如果反着走能够找到足够多的数
        p = t[p][!c], res += (1ll << i);
      else  // 上一位不同时一定比相同时的异或和更大
        rank -= cnt[t[p][!c]], p = t[p][c];
    }
    return res;
  }
} trie;

u64 pxor[MAX_N];
u32 N, K, cur_rnk[MAX_N];
priority_queue<PII> heap;

int main() {
  N = read<u32>();
  K = read<u32>() << 1;

  trie.insert(pxor[0] = 0);

  for (int i = 1; i <= N; i++) {
    pxor[i] = pxor[i - 1] ^ read<u64>();
    trie.insert(pxor[i]);
  }

  for (int i = 0; i <= N; i++) {
    u64 t = trie.find(pxor[i], cur_rnk[i] = 1);
    heap.emplace(t, i);
  }

  u64 ans = 0;

  do {
    auto [sum, idx] = heap.top();
    heap.pop();
    ans += sum;
    heap.emplace(trie.find(pxor[idx], ++cur_rnk[idx]), idx);
  } while (--K);

  write(ans >> 1), putchar('\n');
  return fflush(stdout), 0;
}
