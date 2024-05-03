#include <bitset>
#include <vector>
#include <iostream>
#include <algorithm>

namespace FastIO {
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2;
  char pbuf[MAX_BUF], *pp = pbuf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++)
#define putchar(c) (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c)
#define flush() ((pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout))

  template <typename T>
  inline T read() {
    T var = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') (ch == '-') && (f = -f), ch = getchar();
    while (ch >= '0' && ch <= '9') var = var * 10 + ch - '0', ch = getchar();
    return var * f;
  }

  template <typename T>
  inline void write(T x) {
    static int stack[40];
    int top = 0;
    if (x < 0) putchar('-'), x = -x;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

using l64 = long long;
using PII = std::pair<int, int>;

const int MAX_V = 2.5e5 + 5;
const int INF = 2e9;

int N, logN;
std::vector<PII> adj[MAX_V], adjv[MAX_V];

std::vector<int> key;
std::bitset<MAX_V> vis;

int dfn[MAX_V], depth[MAX_V], dist[MAX_V], ts;
int anc[19][MAX_V], min_w[19][MAX_V];

l64 f[MAX_V];

void DFS(int u, int p) {
  dfn[u] = ++ts;
  depth[u] = depth[p] + 1;
  anc[0][u] = p;
  for (int i = 1; i < logN; ++i) {
    anc[i][u] = anc[i - 1][anc[i - 1][u]];
    min_w[i][u] = std::min(min_w[i - 1][u], min_w[i - 1][anc[i - 1][u]]);
  }

  for (auto [v, w] : adj[u])
    if (v != p) {
      dist[v] = dist[u] + w;
      min_w[0][v] = w;
      DFS(v, u);
    }
}

PII query(int u, int v) {
  if (depth[u] > depth[v]) std::swap(u, v);

  int ret_w = INF;

  for (int i = logN - 1; ~i; --i)
    if (depth[v] - depth[u] >= (1 << i)) {
      ret_w = std::min(ret_w, min_w[i][v]);
      v = anc[i][v];
    }

  if (u == v) return PII(u, ret_w);

  for (int i = logN - 1; ~i; --i)
    if (anc[i][u] != anc[i][v]) {
      ret_w = std::min({ret_w, min_w[i][u], min_w[i][v]});
      u = anc[i][u], v = anc[i][v];
    }

  return PII(anc[0][u], std::min({ret_w, min_w[0][u], min_w[0][v]}));
}

void DP(int u) {
  f[u] = 0;
  for (auto [v, w] : adjv[u]) {
    DP(v);
    if (vis.test(v)) f[u] += w;
    else f[u] += std::min(f[v], (l64)w);
  }
  adjv[u].clear();
}

int main() {
  N = read<int>();
  logN = std::max(19, std::__lg(N) + 1);

  for (int i = 1, u, v, w; i < N; ++i) {
    u = read<int>(), v = read<int>(), w = read<int>();
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  DFS(1, 0);

  int Q = read<int>();

  auto cmp = [&](int x, int y) { return dfn[x] < dfn[y]; };

  while (Q--) {
    int K = read<int>();
    key.clear(), vis.reset(), key.reserve(K << 1);

    for (int i = 0, t; i < K; ++i) key.push_back(t = read<int>()), vis.set(t);
    std::sort(key.begin(), key.end(), cmp);
    for (int i = 0; i < K - 1; ++i) key.push_back(query(key[i], key[i + 1]).first);
    key.push_back(1);
    std::sort(key.begin(), key.end(), cmp);
    key.erase(std::unique(key.begin(), key.end()), key.end());

    for (size_t i = 0; i < key.size() - 1; ++i) {
      auto [LCA, w] = query(key[i + 1], query(key[i], key[i + 1]).first);
      adjv[LCA].emplace_back(key[i + 1], w);
    }

    DP(key.front());
    write(f[key.front()]), putchar('\n');
  }

  flush(), fflush(stdout);
  return 0;
}
