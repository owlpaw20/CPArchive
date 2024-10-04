#include <bits/stdc++.h>

namespace FastIO {
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2;
  char pbuf[MAX_BUF], *pp = pbuf;

  char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }
  void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  void flush() { (pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout); }

  template <typename T>
  T read() {
    short int f = 1;
    T var = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9') var = var * 10 + ch - '0', ch = getchar();
    return var * f;
  }

  template <typename T>
  void write(T x) {
    static short int stack[40];
    if (x < 0) putchar('-'), x = -x;
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

using i64 = long long;
using PII = std::pair<int, int>;
using PLI = std::pair<i64, int>;

const int MAX_N = 5e4 + 5;  // 注意 LibreOJ 上本题的数据范围扩大为 3e5
const int MAX_LG = 16;

int N, M;
std::vector<std::vector<PII>> g;

int fa[MAX_LG + 1][MAX_N];
i64 dist[MAX_LG + 1][MAX_N];

// 预处理树上倍增所需要的信息
void BFS(int st) {
  std::bitset<MAX_N> vis;

  std::queue<int> q;
  q.push(st);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    if (vis.test(u)) continue;
    vis.set(u);

    for (auto [v, w] : g[u]) {
      if (vis.test(v)) continue;

      fa[0][v] = u;
      dist[0][v] = w;

      for (int i = 1; i <= MAX_LG; ++i) {
        fa[i][v] = fa[i - 1][fa[i - 1][v]];
        dist[i][v] = dist[i - 1][v] + dist[i - 1][fa[i - 1][v]];
      }

      q.push(v);
    }
  }
}

int a[MAX_N];
std::bitset<MAX_N> isCap, isUncap;

bool check(i64 x) {
  std::vector<PLI> extLoc;
  isCap.reset(), isUncap.reset();

  std::function<bool(int)> DFS = [&](int u) -> bool {
    if (isCap.test(u)) return true;
    if (u != 1 && g[u].size() == 1) return false;

    for (auto [v, w] : g[u])
      if (v != fa[0][u] && !DFS(v))
        return false;

    return true;
  };

  for (int i = 1; i <= M; ++i) {
    int loc = a[i];
    i64 timeUsed = 0;

    // 将所有军队向根移动
    for (int j = MAX_LG; ~j; --j)
      if (fa[j][loc] > 1 && timeUsed + dist[j][loc] <= x)  // 根据题目，不能移动到根
        timeUsed += dist[j][loc], loc = fa[j][loc];        // 通过树上倍增进行移动

    // 如果有军队能够到达根节点，那么考虑用其覆盖其他的子树
    if (fa[0][loc] == 1 && timeUsed + dist[0][loc] <= x) {  // 统计能够到达根的军队
      i64 timeLeft = x - timeUsed - dist[0][loc];           // 计算到达根节点后还剩多少时间
      extLoc.emplace_back(timeLeft, loc);                   // 暂存其剩余时间和原位置
    } else                                                  // 不能到达根节点的军队
      isCap.set(loc);                                       // 就在末位置驻扎
  }

  for (auto [v, w] : g[1])  // 枚举根的儿子
    if (!DFS(v))            // 如果当前儿子为根的子树中存在叶子没有被覆盖
      isUncap.set(v);       // 标记当前子树为未覆盖

  std::vector<i64> extTime;

  // 枚举能够到达根的军队
  for (auto [timeLeft, loc] : extLoc)
    // 如果存在能够到达根但不能返回，且其原子树有叶子未覆盖的，就驻扎在原子树树根
    if (isUncap.test(loc) && dist[0][loc] > timeLeft) isUncap[loc] = false;
    else extTime.push_back(timeLeft);  // 剩下的军队就可以用来派遣到其他的根辖子树去

  std::vector<i64> reqTime;

  for (auto [v, w] : g[1])            // 枚举根的儿子
    if (isUncap.test(v))              // 如果当前儿子为根的子树被标记存在叶子没有覆盖
      reqTime.push_back(dist[0][v]);  // 将根到该儿子的距离存储下来

  // 如果多余的军队数量没有剩下需要覆盖的子树数量多，那么显然该方案不成立
  if (reqTime.size() > extTime.size()) return false;

  // 对剩下的军队多余的时间，以及根到未覆盖子树的儿子所需要的时间，分别进行排序
  std::sort(extTime.begin(), extTime.end());
  std::sort(reqTime.begin(), reqTime.end());

  // 分别从空余时间最小、所需时间最短的军队和需求开始考虑
  size_t i = 0, j = 0;

  while (i < extTime.size() && j < reqTime.size())
    if (extTime[i] >= reqTime[j]) ++i, ++j;  // 如果空余时间足以满足需求，则移动两个指针
    else ++i;                                // 否则考虑空余时间更多的军队

  return j == reqTime.size();  // 如果所有需求均被满足，那么该方案成立
}

int main() {
  N = read<int>();
  g.resize(N + 1);

  for (int i = 1, u, v, w; i < N; ++i) {
    u = read<int>(), v = read<int>(), w = read<int>();
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  BFS(1);

  M = read<int>();
  for (int i = 1; i <= M; ++i) a[i] = read<int>();

  i64 l = 0, r = 1e18;

  while (l < r) {
    i64 mid = (l + r) >> 1;
    if (check(mid)) r = mid;
    else l = mid + 1;
  }

  write(r == 1e18 ? -1 : r), flush();  // 需要考虑无解
  return 0;
}
