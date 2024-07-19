#include <cstring>
#include <iostream>

using PII = std::pair<int, int>;

constexpr int MAX_N = 22;
constexpr int MAX_STATES = 1 << MAX_N;

int N, M;
int know[MAX_N];
int f[MAX_STATES];
PII trace[MAX_STATES];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  if (M == N * (N - 1) / 2) {
    std::cout << 0 << std::endl;
    return 0;
  }

  while (M--) {
    static int u, v;
    std::cin >> u >> v, --u, --v;
    know[u] |= 1 << v;
    know[v] |= 1 << u;
  }

  memset(f, 0x3F, sizeof(int) * (1 << N));

  for (int i = 0; i < N; ++i)
    f[1 << i] = 0, trace[1 << i].second = -1;

  for (int st = 0; st < (1 << N); ++st)
    for (int i = 0; i < N; ++i)
      if (((st >> i) & 1) && f[st | know[i]] > f[st] + 1)
        f[st | know[i]] = f[st] + 1, trace[st | know[i]] = {st, i};

  int st = (1 << N) - 1;
  std::cout << f[st] << '\n';

  while (trace[st].first) {
    if (trace[st].second != -1) std::cout << trace[st].second + 1 << ' ';
    st = trace[st].first;
  }

  std::cout.flush();
  return 0;
}
