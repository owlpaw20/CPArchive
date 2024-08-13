#include <bits/stdc++.h>

const int MAX_N = 10;
const int MAX_M = 1e5 + 5;
const int MAX_ST = 1 << 10;

int N, w[MAX_N];
int M, l[MAX_M], v[MAX_M];

int d[MAX_ST + 5];
int p[MAX_N], f[MAX_N];  // f[i] denotes the minimum distance from the first to the i-th camel

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  for (int i = 1; i <= N; ++i) std::cin >> w[i];
  for (int i = 1; i <= M; ++i) std::cin >> l[i] >> v[i];

  int maxW = *std::max_element(w + 1, w + N + 1);
  int minV = *std::min_element(v + 1, v + M + 1);
  if (maxW > minV) return std::cout << -1 << std::endl, 0;

  // calculate the minimum valid distance between each group of camel, represented in bitmask
  for (int state = 1; state < (1 << N); ++state) {
    int sumW = 0;
    for (int i = 0; i < N; ++i)
      if ((state >> i) & 1)
        sumW += w[i + 1];
    for (int i = 1; i <= M; ++i)
      if (v[i] < sumW)
        d[state] = std::max(d[state], l[i]);
  }

  std::iota(p + 1, p + N + 1, 1);  // initiate the permutation array
  int ans = std::numeric_limits<int>::max();

  do {
    memset(f, 0, sizeof(int) * (N + 1));

    for (int i = 1; i <= N; ++i) {               // iterate through the camels and update their f[i]
      int state = 1 << (p[i] - 1);               // the initial state contains the last camel
      for (int j = i - 1; j; --j) {              // iterate through the previous camels
        state |= 1 << (p[j] - 1);                // add them to the state one at a time
        f[i] = std::max(f[i], f[j] + d[state]);  // update f[i] by how much distance do the previous camels need when together
      }
    }

    ans = std::min(ans, f[N]);  // update the answer accordingly
  } while (std::next_permutation(p + 1, p + N + 1));

  std::cout << ans << std::endl;
  return 0;
}
