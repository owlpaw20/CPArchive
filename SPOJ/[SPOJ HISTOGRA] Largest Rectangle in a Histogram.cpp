#include <stack>
#include <cstring>
#include <iostream>

using namespace std;

using ll = long long;

const int N = 1e5 + 10;
ll n, tmp;

struct node {
  ll height = 0, width = 0;
};

struct stack {
  node e[N];
  ll t = 0;
  void push(node x) {
    e[++t] = x;
    return;
  }
  void pop() {
    t--;
    return;
  }
  node top() {
    return e[t];
  }
  bool empty() {
    return !t;
  }
} st;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  while (1) {
    cin >> n;
    if (!n) break;
    ll ans = -1;
    int h[N] = {0};
    for (int i = 1; i <= n; i++) cin >> h[i];
    h[n + 1] = 0;  // !!
    for (int i = 1; i <= n + 1; i++) {
      ll wd = 0;
      while (!st.empty() && h[i] <= st.top().height) {
        wd += st.top().width;
        ans = max(ans, wd * st.top().height);
        st.pop();
      }
      st.push({h[i], wd + 1});
    }
    cout << ans << endl;
    while (!st.empty()) st.pop();
  }
  return 0;
}
