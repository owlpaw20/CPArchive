#pragma GCC optimize("O2,unroll-loops")

#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

int n, sum, len;
vector<int> length;
vector<bool> vis;

bool DFS(int group, int now_len, int now_idx) {
  if (group * len == sum)  // 如果已经到达了总长度
    return true;           // 则退出搜索并返回成功

  if (now_len == len)             // 如果当前木棒已经拼接完成
    return DFS(group + 1, 0, 0);  // 则进入新的一根木棒

  for (int i = now_idx; i < n; i++) {
    if (vis[i] || now_len + length[i] > len)  // 如果不能加上这一根
      continue;                               // 跳出循环

    vis[i] = true;                               // 否则这一根合法
    if (DFS(group, now_len + length[i], i + 1))  // 加上这一根并递归搜索
      return true;
    vis[i] = false;

    // 如果当前是木棒的第一根或最后一根木棍并且没有成功
    // 则根据木棒的无序性，该分支无论如何一定失败
    if (now_len == 0 || now_len + length[i] == len)
      return false;

    // 去除冗余分支
    // 相同长度的木棍不再搜索
    int j = i;
    while (j < n && length[j] == length[i]) j++;
    i = j - 1;
  }

  return false;
}

void solve(int n) {
  vis.clear();
  length.clear();
  length.resize(n, 0);
  vis.resize(n, false);

  sum = 0, len = 0;
  for (int i = 0; i < n; i++) {
    cin >> length[i];
    sum += length[i];
    len = max(len, length[i]);  // 从最长一根木棍的长度开始，减少搜索量
  }

  // 降序排序，优化搜索顺序
  sort(length.begin(), length.end(), greater<int>());

  for (; len <= sum; len++)
    if (sum % len == 0 && DFS(0, 0, 0))    // 如果当前长度合法并搜索成功
      return (void)(cout << len << endl);  // 则输出最短长度
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  while (cin >> n, n) solve(n);

  fflush(stdout);
  return 0;
}
