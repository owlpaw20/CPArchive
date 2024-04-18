#include <cstdlib>
#include <iostream>
using namespace std;
using i64 = long long;

const int N = 1e5 + 10;

i64 n, m, p1, s1, p2, s2, c[N];
i64 p[N], A, B;

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> c[i];
  cin >> m >> p1 >> s1 >> s2;
  c[p1] += s1;
  i64 pos = m;
  for (int i = 1; i <= n; i++) {
    p[i] = c[i] * abs(m - i);
    if (i < m)
      A += p[i];
    else if (i > m)
      B += p[i];
  }
  i64 diff = abs(A - B);
  for (int i = 1; i <= n; i++) {
    i64 a = A, b = B;
    if (i < m)
      a += s2 * abs(i - m);
    else if (i > m)
      b += s2 * abs(i - m);
    if (abs(a - b) < diff) {
      diff = abs(a - b);
      pos = i;
    }
  }
  cout << pos << endl;
  return 0;
}
