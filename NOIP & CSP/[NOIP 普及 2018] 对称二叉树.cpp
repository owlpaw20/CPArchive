#include <iostream>

using namespace std;

const int N = 1e6 + 10;

struct TreeNode {
  int l, r, v;
};

int n, ans = -1;
TreeNode t[N];

bool check(int l, int r) {
  if (l == -1 && r == -1) return true;
  if (l == -1 || r == -1) return false;
  if (t[l].v != t[r].v) return false;
  return check(t[l].l, t[r].r) && check(t[r].l, t[l].r);
}

int node_count(int u) {
  if (u == -1) return 0;
  return node_count(t[u].l) + node_count(t[u].r) + 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> t[i].v;
  for (int i = 1; i <= n; i++) cin >> t[i].l >> t[i].r;
  for (int i = 1; i <= n; i++)
    if (check(i, i))
      ans = max(ans, node_count(i));

  cout << ans << '\n';
  return 0;
}
