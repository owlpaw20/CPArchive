#include <queue>
#include <iostream>

#define endl '\n'

using PII = std::pair<int, int>;

const int MAX_N = 3e3 + 5;

int n, p, s;
int P[MAX_N], S[MAX_N];
int vis[MAX_N];

std::priority_queue<PII> A, B, D;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> p >> s;

  for (int i = 1; i <= n; ++i)
    std::cin >> P[i], A.emplace(P[i], i);

  int ans = 0;

  while (p--) {
    auto [a, i] = A.top();
    vis[i] = 1;
    ans += a;
    A.pop();
  }

  for (int i = 1; i <= n; ++i) {
    std::cin >> S[i];
    B.emplace(S[i], i);
    if (vis[i]) D.emplace(S[i] - P[i], i);
  }

  while (s--) {
    while (!A.empty() && vis[A.top().second]) A.pop();
    while (!B.empty() && vis[B.top().second]) B.pop();

    auto [a, i] = A.top();
    auto [b, j] = B.top();
    auto [d, k] = D.top();

    if (b > a + d) {
      ans += b;
      vis[j] = 2;
      B.pop();
    }

    else {
      ans += a + d;
      vis[i] = 1;
      vis[k] = 2;
      A.pop(), D.pop();
      D.emplace(S[i] - P[i], i);
    }
  }

  std::cout << ans << endl;

  for (int i = 1; i <= n; ++i)
    if (vis[i] == 1)
      std::cout << i << ' ';

  std::cout << endl;

  for (int i = 1; i <= n; ++i)
    if (vis[i] == 2)
      std::cout << i << ' ';

  std::cout << endl;

  return fflush(stdout), 0;
}
