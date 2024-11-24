#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 200'005;

int N, M, p1, p2, a[MAX_N];
int gl[MAX_N], gr[MAX_N];

// 通过单调栈预处理 a[i] 左侧和右侧最近的 > a[i] 的位置
void prep() {
  std::stack<int> st;

  for (int i = 1; i <= N; ++i) {
    while (!st.empty() && a[st.top()] < a[i]) st.pop();
    gl[i] = st.empty() ? 0 : st.top();
    st.push(i);
  }

  while (!st.empty()) st.pop();

  for (int i = N; i >= 1; --i) {
    while (!st.empty() && a[st.top()] < a[i]) st.pop();
    gr[i] = st.empty() ? N + 1 : st.top();
    st.push(i);
  }
}

struct QueryData {
  int l, r, p, v, id;
  inline bool operator<(const QueryData& rhs) const { return p < rhs.p; }
} q[MAX_N * 2], s[MAX_N * 3];

// 在 q 中，l 和 r 分别表示询问端点，p 表示前缀和的端点，v 表示最终计算时需要考虑的常数
// 在 s 中，l 和 r 分别表示产生贡献的区间端点范围，p 表示统计贡献的位置，v 表示统计贡献的大小

struct SegT {
  struct Node {
    i64 sum, tag;
    void modify(i64 v, int len) { sum += v * len, tag += v; }
  } tr[MAX_N << 2];

  void pushdown(int u, int nl, int nr) {
    if (!tr[u].tag) return;
    int mid = (nl + nr) >> 1;
    tr[u << 1].modify(tr[u].tag, mid - nl + 1);
    tr[u << 1 | 1].modify(tr[u].tag, nr - mid);
    tr[u].tag = 0;
  }

  void upd(int l, int r, i64 v, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u].modify(v, nr - nl + 1);
    pushdown(u, nl, nr);
    int mid = (nl + nr) >> 1;
    if (l <= mid) upd(l, r, v, u << 1, nl, mid);
    if (r > mid) upd(l, r, v, u << 1 | 1, mid + 1, nr);
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
  }

  i64 qry(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u].sum;
    pushdown(u, nl, nr);
    int mid = (nl + nr) >> 1;
    if (r <= mid) return qry(l, r, u << 1, nl, mid);
    if (l > mid) return qry(l, r, u << 1 | 1, mid + 1, nr);
    return qry(l, r, u << 1, nl, mid) + qry(l, r, u << 1 | 1, mid + 1, nr);
  }
} T;

i64 ans[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M >> p1 >> p2;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  prep();

  for (int i = 1, l, r; i <= M; ++i) {
    std::cin >> l >> r;
    q[i] = {l, r, l - 1, -1, i};  // 最后统计答案采用类似于前缀和的方式
    q[i + M] = {l, r, r, 1, i};   // 右端点处的总贡献减去左端点前的总贡献
    ans[i] += i64(r - l) * p1;    // 相邻两数一定满足贡献 p1 的条件，需要特判
  }

  std::sort(q + 1, q + M + M + 1);  // 对询问进行离线处理

  int cnt = 0;

  // 统计处理所有计算贡献的位置
  for (int i = 1; i <= N; ++i) {
    // [gl[i], gr[i]] 有 p1 的贡献，该贡献的答案在完成一整个区间后统计，即 gr[i] 处（这里互换 gl[i] 和 gr[i] 是等效的）
    if (gl[i] >= 1 && gr[i] <= N) s[++cnt] = {gl[i], gl[i], gr[i], p1, -1};
    // 区间左端点在 [gl[i] + 1, i - 1]、右端点在 gr[i]，则产生 p2 的贡献，在右端点 gr[i] 处统计
    if (gl[i] + 1 <= i - 1 && gr[i] <= N) s[++cnt] = {gl[i] + 1, i - 1, gr[i], p2, -1};
    // 区间左端点在 gl[i]，右端点在 [i + 1, gr[i] - 1]，则产生 p2 的贡献，在左端点 gl[i] 处统计
    if (gl[i] >= 1 && gr[i] - 1 >= i + 1) s[++cnt] = {i + 1, gr[i] - 1, gl[i], p2, -1};
  }

  std::sort(s + 1, s + cnt + 1);

  int j = 1, k = 1;
  while (!q[j].p) ++j;  // 询问的左端点为 0 时显然不需要考虑

  for (int i = 1; i <= N; ++i) {
    while (k <= cnt && s[k].p == i) T.upd(s[k].l, s[k].r, s[k].v), ++k;                     // 累计贡献
    while (j <= M + M && q[j].p == i) ans[q[j].id] += T.qry(q[j].l, q[j].r) * q[j].v, ++j;  // 统计答案
  }

  for (int i = 1; i <= M; ++i) std::cout << ans[i] << '\n';
  return 0;
}
