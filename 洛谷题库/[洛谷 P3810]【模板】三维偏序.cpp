#include <bits/stdc++.h>

using TUP = std::tuple<int, int, int>;

using std::get;

const int MAX_N = 1e5 + 5;
const int MAX_V = 2e5 + 5;

int N, k, M;

struct Tuple {
  int a, b, c, cnt, ans;

  Tuple() {}
  Tuple(TUP _x, int _y) : a(get<0>(_x)), b(get<1>(_x)), c(get<2>(_x)), cnt(_y), ans(0) {}

  bool operator<(const Tuple& t) const { return (b != t.b) ? (b < t.b) : (c < t.c); }
} a[MAX_N];

std::map<TUP, int> vis;

struct Fenwick {
  int c[MAX_V];
  void upd(int x, int v) { for (; x <= k; x += x & -x) c[x] += v; }
  int qry(int x) { int sum = 0; for (; x; x -= x & -x) sum += c[x]; return sum; }
} T;

void CDQ(int l, int r) {
  if (l == r) return;
  int mid = (l + r) >> 1;
  CDQ(l, mid), CDQ(mid + 1, r);

  // 按照 b 排序
  std::sort(a + l, a + mid + 1);
  std::sort(a + mid + 1, a + r + 1);

  // 处理左右两半之间的贡献
  for (int i = l, j = mid + 1; j <= r; ++j) {
    while (i <= mid && a[i].b <= a[j].b) T.upd(a[i].c, a[i].cnt), ++i;
    a[j].ans += T.qry(a[j].c);
  }

  // 还原树状数组
  for (int i = l; i <= mid && a[i].b <= a[r].b; ++i) T.upd(a[i].c, -a[i].cnt);
}

int ans[MAX_V];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> k;

  // 输入、根据 a 排序，并去重
  for (int i = 1, a, b, c; i <= N; ++i) std::cin >> a >> b >> c, ++vis[TUP(a, b, c)];
  for (auto [t, w] : vis) ++M, a[M] = Tuple(t, w);

  // 执行陈丹琦分治
  CDQ(1, M);

  // 偏序关系不严格，但下标不能相同，所以对于相同的 x 个元素，答案为原答案 + (x - 1)
  for (int i = 1; i <= M; ++i) ans[a[i].ans + a[i].cnt - 1] += a[i].cnt;
  for (int i = 0; i < N; ++i) std::cout << ans[i] << '\n';
  
  std::cout.flush();
  return 0;
}
