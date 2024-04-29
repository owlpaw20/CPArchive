#include <cstring>
#include <iostream>

#define endl '\n'

const int MAX_V = 2e5 + 5;
const int MAX_E = 4e5 + 5;
const int MOD = 10007;

int N, w[MAX_V], ans_1, ans_2;
int ed[MAX_E], nx[MAX_E], head[MAX_V], idx;

inline void connect(const int u, const int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

void calc(int u) {
  int max_c = 0, smax_c = 0, sum_w = 0;

  for (int i = head[u], v; ~i; i = nx[i]) {
    if (w[v = ed[i]] >= max_c) {
      smax_c = max_c;
      max_c = w[v];
    } else if (w[v] > smax_c)
      smax_c = w[v];
    (ans_2 += sum_w * w[v]) %= MOD;
    (sum_w += w[v]) %= MOD;
  }

  ans_1 = std::max(ans_1, max_c * smax_c);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  memset(head, -1, sizeof(int) * (N + 1));

  for (int i = 1, u, v; i < N; ++i) {
    std::cin >> u >> v;
    connect(u, v);
    connect(v, u);
  }
  for (int i = 1; i <= N; ++i) std::cin >> w[i];
  for (int i = 1; i <= N; ++i) calc(i);

  std::cout << ans_1 << ' ' << ans_2 * 2 % MOD << endl;
  fflush(stdout);
  return 0;
}
