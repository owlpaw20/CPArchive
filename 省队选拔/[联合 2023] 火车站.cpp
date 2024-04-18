#include <iostream>
#include <algorithm>
#define l first
#define r second
using namespace std;
using PII = pair<int, int>;

const int N = 2e5 + 10;

PII rail[N];
bool flag[N];
int n, m, x, cnt;

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> m >> x;
  for (int i = 1; i <= m; i++)
    cin >> rail[i].l >> rail[i].r;

  int maxr = x;
  sort(rail + 1, rail + m + 1);
  for (int i = 1; i <= m && rail[i].l <= maxr; i++)
    if (rail[i].r > x)
      maxr = max(maxr, rail[i].r), flag[rail[i].r] = true;

  int minl = x;
  auto cmp = [&](PII a, PII b) {
    return a.r > b.r;
  };
  sort(rail + 1, rail + m + 1, cmp);
  for (int i = 1; i <= m && rail[i].r >= minl; i++)
    if (rail[i].l < x)
      minl = min(minl, rail[i].l), flag[rail[i].l] = true;

  for (int i = 1; i <= n; i++)
    if (flag[i])
      cout << i << ' ';
  return putchar('\n') && 0;
}
