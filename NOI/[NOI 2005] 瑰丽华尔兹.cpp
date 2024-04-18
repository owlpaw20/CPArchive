#include <deque>
#include <cstring>
#include <iostream>

#define endl '\n'

using PII = std::pair<int, int>;  // first = dp_val, second = time

const int MAX_N = 2e2 + 5;
const int MAX_M = 2e2 + 5;
const int MAX_K = 2e2 + 5;

const int dx[] = {0, -1, 1, 0, 0};
const int dy[] = {0, 0, 0, -1, 1};

int N, M, x, y, K;
bool hall[MAX_N][MAX_M];

// f[i][j][k] 表示在第 i 个时间段内，起点处于 (j, k) 位置时，最远能够走多少步
// f[i] 这一维被滚动数组优化掉了

int f[MAX_N][MAX_M];

int solve(int x, int y, const int d, const int len) {
  std::deque<PII> q;

  int ret = 0;

  for (int i = 1;; ++i, x += dx[d], y += dy[d]) {
    if (x < 1 || x > N || y < 1 || y > M) break;

    // 如果遇到障碍物，则说明已经走到了头，清空队列并从当前方向上的下一格重新 DP
    if (hall[x][y]) {
      q.clear();
      continue;
    }

    // 单调递减队列，如果当前队尾的最远步数（DP 距离 + 随时间继续移动的距离）比当前位置的 DP 值小，则弹出
    while (!q.empty() && q.back().first + i - q.back().second < f[x][y]) q.pop_back();
    q.emplace_back(f[x][y], i);

    // 超出当前时间范围的弹出队列
    while (q.back().second - q.front().second > len) q.pop_front();

    // 计算当前位置的最远距离
    f[x][y] = q.front().first + i - q.front().second;

    ret = std::max(ret, f[x][y]);
  }

  return ret;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M >> x >> y >> K;

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= M; ++j) {
      char ch;
      std::cin >> ch;
      hall[i][j] = (ch == 'x');
    }

  memset(f, 0xCF, sizeof f);
  f[x][y] = 0;

  int ans = 0;

  for (int k = 1, l, r, d; k <= K; ++k) {
    std::cin >> l >> r >> d;
    int len = r - l + 1;

    if (d == 1)                                    // 向北移动
      for (int i = 1; i <= M; ++i)                 // 遍历每一列
        ans = std::max(ans, solve(N, i, d, len));  // 从每一列的最南边一个格子开始向北走

    else if (d == 2)                               // 向南移动
      for (int i = 1; i <= M; ++i)                 // 遍历每一列
        ans = std::max(ans, solve(1, i, d, len));  // 从每一列的最北边一个格子开始向南走

    else if (d == 3)                               // 向西移动
      for (int i = 1; i <= N; ++i)                 // 遍历每一行
        ans = std::max(ans, solve(i, M, d, len));  // 从每一行的最东边一个格子开始向西走

    else if (d == 4)                               // 向东移动
      for (int i = 1; i <= N; ++i)                 // 遍历每一行
        ans = std::max(ans, solve(i, 1, d, len));  // 从每一行的第最西边一个格子开始向东走
  }

  std::cout << ans << endl;
  return fflush(stdout), 0;
}
