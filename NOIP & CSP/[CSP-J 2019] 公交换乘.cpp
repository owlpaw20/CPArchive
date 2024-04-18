#include <iostream>
using namespace std;

const int N = 1e5 + 10;

struct Coupon {
  int c, lmt;
  bool used;
} cp[N];

int n, ans, head = 0, rear = -1;

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n;
  while (n--) {
    int k, c, t;
    cin >> k >> c >> t;
    if (k == 0) {
      ans += c;
      cp[++rear] = (Coupon){
        c, t + 45, false};
    } else {
      while (head <= rear && cp[head].lmt < t) head++;
      bool flag = false;
      for (int i = head; i <= rear; i++)
        if (cp[i].c >= c && cp[i].used == false) {
          flag = true;
          cp[i].used = true;
          break;
        }
      if (!flag) ans += c;
    }
  }
  cout << ans << endl;
  return 0;
}
