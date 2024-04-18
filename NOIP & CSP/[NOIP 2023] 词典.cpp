#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using PSI = pair<string, int>;

const int N = 3e3 + 5;

int n, m;
bool vis[N];
priority_queue<PSI, vector<PSI>, greater<PSI>> heap;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    sort(s.begin(), s.end());  // 取得字符串的最小字典序
    heap.emplace(s, i);        // 将最小字典序连同下标一起存入堆中
  }

  // 对 pair 比大小的第一关键字是其第一元素的值
  while (!heap.empty() && !vis[heap.top().second]) {
    auto [str, idx] = heap.top();
    reverse(str.begin(), str.end());  // 取得字符串的最大字典序
    vis[idx] = true;                  // 标记合法
    heap.pop();                       // 将最小字典序弹出堆
    heap.emplace(str, idx);           // 将最大字典序存入堆
  }

  for (int i = 1; i <= n; i++)
    cout.put('0' + vis[i]);

  cout.put('\n');
  fflush(stdout);
  return 0;
}
