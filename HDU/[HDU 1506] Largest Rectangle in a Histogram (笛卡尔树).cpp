#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 1e5 + 5;

int N;
i64 ans;

struct Node {
  int val, fa, l, r;
} tr[MAX_N];

void ins(int x, int v) {
  int p = x - 1;
  while (tr[p].val > v) p = tr[p].fa;
  tr[x].val = v, tr[x].l = tr[p].r;
  tr[p].r = x, tr[x].fa = p;
  tr[tr[x].l].fa = x;
}

int DFS(int u) {
  if (!u) return 0;
  int width = DFS(tr[u].l) + DFS(tr[u].r) + 1;
  ans = std::max(ans, (i64)width * tr[u].val);
  return width;
}

bool solve() {
  std::cin >> N;
  if (!N) return false;

  memset(tr, 0, sizeof(Node) * (N + 1));
  for (int i = 1, x; i <= N; ++i) std::cin >> x, ins(i, x);

  ans = 0;
  DFS(tr[0].r);
  std::cout << ans << '\n';

  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  while (solve()) continue;

  std::cout.flush();
  return 0;
}
