#include <vector>
#include <climits>
#include <iostream>
using namespace std;

template <class T>
struct monotonic_queue {
  vector<T> data;
  int head, rear;
  void push(T x) {
    data[++rear] = x;
  }
  void pop_front() {
    head++;
  }
  void pop_back() {
    rear--;
  }
  T front() {
    return data[head];
  }
  T back() {
    return data[rear];
  }
  bool empty() {
    return head > rear;
  }
  void reset(int n) {
    head = 0, rear = -1;
    data.clear(), data.resize(n);
  }
};

int n;
vector<int> a;
monotonic_queue<int> q;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  a.resize(n + 5);
  for (int i = 1; i <= n; i++) cin >> a[i];

  int ans = INT_MIN;
  q.reset(n + 5);

  /*  引理：极值一定位于最优选择的区间的左右端点处
      证明：如果极值不在左右端点处，
          则一定可以删除极值位置到区间左或右端点之间的所有元素，
          减小区间长度，从而使答案更优 */

  // 枚举右端点 a[i] 作为最大值的情况，队列从前往后单调递增
  for (int i = 1; i <= n; i++) {
    while (!q.empty() && a[q.front()] > a[i]) q.pop_front();  // 当区间左端点 i 为区间最大值时
    while (!q.empty() && a[i] - a[q.back()] < i - q.back())   // 若 i 的左边有更优的左端点 j
      q.pop_back();                                           // 则 i 距离 j 的长度比 a[i] - a[j] 更小
    q.push(i);
    ans = max(ans, a[i] - a[q.front()] - (i - q.front() + 1));
  }

  q.reset(n + 5);

  // 枚举右端点 a[i] 作为最小值的情况，队列从前往后单调递减
  for (int i = 1; i <= n; i++) {
    while (!q.empty() && a[q.front()] < a[i]) q.pop_front();  // 当区间左端点 i 为区间最小值时
    while (!q.empty() && a[i] - a[q.back()] > q.back() - i)   // 若 i 的左边有更优的左端点 j
      q.pop_back();                                           // 则 i 距离 j 的长度比 a[i] - a[j] 更大
    q.push(i);
    ans = max(ans, a[q.front()] - a[i] - (i - q.front() + 1));
  }

  cout << ans << endl;
  return 0;
}
