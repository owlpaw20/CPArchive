#include <bits/stdc++.h>

namespace FastIO {
  // clang-format off
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2, pbuf[MAX_BUF], *pp = pbuf;
  char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }
  void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  void flush() { (pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout); }
  template <typename T>
  T read() {
    short int f = 1; T var = 0; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -f; ch = getchar(); }
    while (ch >= '0' && ch <= '9') var = var * 10 + ch - '0', ch = getchar();
    return var * f;
  }
  template <typename T>
  void write(T x) {
    static short int stack[40]; int top = 0;
    if (x < 0) putchar('-'), x = -x;
    do stack[top++] = x % 10, x /= 10; while (x);
    while (top) putchar(stack[--top] + 48);
  }
  // clang-format on
}  // namespace FastIO
using namespace FastIO;

using PII = std::pair<int, int>;

const int MAX_N = 500'005;

int N, M;
std::vector<std::vector<PII>> gg;

int dfn[MAX_N], low[MAX_N], ts;
std::stack<int> stk;
bool instk[MAX_N];

int bel[MAX_N], color;
std::vector<std::vector<int>> bcc;

void Tarjan(int u, int e) {
  dfn[u] = low[u] = ++ts;
  stk.push(u), instk[u] = true;

  for (auto [v, id] : gg[u]) {
    if (e == id) continue;
    if (!dfn[v]) Tarjan(v, id), low[u] = std::min(low[u], low[v]);
    else if (instk[v]) low[u] = std::min(low[u], dfn[v]);
  }

  if (dfn[u] == low[u]) {
    ++color;
    int v;
    do instk[v = stk.top()] = false, bel[v] = color, stk.pop();
    while (v != u);
  }
}

int main() {
  N = read<int>(), M = read<int>();
  gg.resize(N + 1);

  for (int i = 1, u, v; i <= M; ++i) {
    u = read<int>(), v = read<int>();
    gg[u].emplace_back(v, i);
    gg[v].emplace_back(u, i);
  }

  for (int i = 1; i <= N; ++i)
    if (!dfn[i])
      Tarjan(i, 0);

  bcc.resize(color + 1);
  for (int i = 1; i <= N; ++i) bcc[bel[i]].push_back(i);

  write(color), putchar('\n');

  for (int i = 1; i <= color; ++i) {
    write(bcc[i].size());
    for (int u : bcc[i]) putchar(' '), write(u);
    putchar('\n');
  }

  return flush(), 0;
}
