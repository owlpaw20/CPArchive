#pragma GCC optimize("O2")
#include <iostream>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using MAXHEAP = __gnu_pbds::priority_queue<int, less<int>>;
using MINHEAP = __gnu_pbds::priority_queue<int, greater<int>>;

int T;
MAXHEAP maxheap;  // 大根堆维护排名为 [1, I / 2] 的元素
MINHEAP minheap;  // 小根堆维护排名为 (I / 2, I] 的元素

void solve() {
  int C, n;
  cin >> C >> n;
  cout << C << ' ' << (n + 1) / 2 << endl;
  maxheap.clear(), minheap.clear();

  int output_lmt = 0;

  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    if (minheap.empty())          // 第一个元素默认放在小根堆
      minheap.push(x);            // 小根堆堆顶维护的就是当前中位数
    else if (x >= minheap.top())  // 如果当前元素比小根堆堆顶要大
      minheap.push(x);            // 则一定比大根堆所有元素更大，故压入小根堆
    else                          // 否则
      maxheap.push(x);            // 压入大根堆

    if (maxheap.size() > minheap.size())           // 如果大根堆比小根堆元素多
      minheap.push(maxheap.top()), maxheap.pop();  // 则调整元素位置
    if (minheap.size() > maxheap.size() + 1)       // 如果小根堆除了堆顶还比大根堆元素多
      maxheap.push(minheap.top()), minheap.pop();  // 则调整元素位置

    if (i & 1) {
      cout << minheap.top() << ' ';
      output_lmt += 1;
      if (output_lmt >= 10)
        cout.put('\n'), output_lmt -= 10;
    }
  }

  if (output_lmt) cout.put('\n');
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> T;
  while (T--) solve();

  fflush(stdout);
  return 0;
}
