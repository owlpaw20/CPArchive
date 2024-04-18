#include <tuple>
#include <vector>
#include <iostream>

using namespace std;
using i64 = long long;
using COW = tuple<int, int>;

int n;
i64 T;
vector<i64> lst;
vector<COW> cows;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> T;
  lst.resize(n);
  cows.resize(n);
  for (int i = 0; i < n; i++) {
    auto& [pos, v] = cows[i];
    cin >> pos >> v;
    lst[i] = v * T + pos;
  }

  int ans = 1;
  for (int i = n - 2; i >= 0; i--)
    if (lst[i] >= lst[i + 1])
      lst[i] = lst[i + 1];
    else
      ans += 1;

  cout << ans << '\n';
  fflush(stdout);
  return 0;
}
