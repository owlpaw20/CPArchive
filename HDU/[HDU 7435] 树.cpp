#pragma GCC optimize("O2,unroll-loops,inline")

#include <bits/stdc++.h>

const int MAX_N = 5e5 + 5;
const int MAX_M = 1e6 + 5;
const int MAX_V = 1e6;

using u64 = unsigned long long;

int N, a[MAX_N];
int head[MAX_N], ed[MAX_M], nx[MAX_M], idx;
void connect(int u, int v) { ed[++idx] = v, nx[idx] = head[u], head[u] = idx; }

struct SegT {
  struct Node {
    int lc, rc, size;
    u64 sum, sq_sum, contrib;
  } tr[MAX_M * 20];

  int size;

  void pushup(int u, int lc, int rc) {
    tr[u].sum = tr[lc].sum + tr[rc].sum;
    tr[u].size = tr[lc].size + tr[rc].size;
    tr[u].sq_sum = tr[lc].sq_sum + tr[rc].sq_sum;
    tr[u].contrib = tr[lc].contrib + tr[rc].contrib + tr[lc].size * tr[rc].sq_sum - tr[lc].sum * tr[rc].sum;
  }

  void upd(int x, int& u, int nl = 1, int nr = MAX_V) {
    if (!u) u = ++size;
    if (nl == nr) {
      ++tr[u].size;
      tr[u].sum = (u64)x * tr[u].size;
      tr[u].sq_sum = (u64)x * x * tr[u].size;
      return;
    }
    int mid = (nl + nr) >> 1;
    if (x <= mid) upd(x, tr[u].lc, nl, mid);
    else upd(x, tr[u].rc, mid + 1, nr);
    pushup(u, tr[u].lc, tr[u].rc);
  }

  void merge(int& u, int v, int nl = 1, int nr = MAX_V) {
    if (!v) return;
    if (!u) return u = v, void();
    if (nl == nr) {
      tr[u].sum += tr[v].sum;
      tr[u].size += tr[v].size;
      tr[u].sq_sum += tr[v].sq_sum;
      return;
    }
    int mid = (nl + nr) >> 1;
    merge(tr[u].lc, tr[v].lc, nl, mid);
    merge(tr[u].rc, tr[v].rc, mid + 1, nr);
    pushup(u, tr[u].lc, tr[u].rc);
  }
} T;

int rt[MAX_N];
u64 ans[MAX_N];

void DFS(int u, int fa) {
  T.upd(a[u], rt[u]);
  for (int i = head[u]; ~i; i = nx[i])
    if (ed[i] != fa)
      DFS(ed[i], u), T.merge(rt[u], rt[ed[i]]);
  ans[u] = T.tr[rt[u]].contrib << 1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  memset(head, -1, sizeof(int) * (N + 1));
  for (int i = 1, u, v; i < N; ++i) std::cin >> u >> v, connect(u, v), connect(v, u);
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  DFS(1, 0);

  u64 _ans = 0;
  for (int i = 1; i <= N; ++i) _ans ^= ans[i];

  std::cout << _ans << std::endl;
  return 0;
}
