#include <iostream>
#include <algorithm>
#include <unordered_map>

#define endl '\n'

using l64 = long long;

const int MAX_N = 2e3 + 5;
const int MOD = 1e9 + 7;

int n, K;
int bin_coeff[MAX_N][MAX_N];
std::unordered_map<std::string, int> vis;

int f[2][MAX_N];  // f[i][j] 表示前 i 组单词中，恰好构成 j 对相似单词的方案数

void prep(int n) {
  bin_coeff[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    bin_coeff[i][0] = bin_coeff[i][i] = 1;
    for (int j = 1; j <= i; ++j)
      bin_coeff[i][j] = (bin_coeff[i - 1][j - 1] + bin_coeff[i - 1][j]) % MOD;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> K;

  int max_cnt = 0;

  for (int i = 1; i <= n; ++i) {
    std::string s;
    std::cin >> s;
    std::sort(s.begin(), s.end());
    max_cnt = std::max(max_cnt, ++vis[s]);
  }

  prep(max_cnt);

  f[1][0] = 1;

  int cur = 1;
  for (auto [str, rep] : vis) {
    cur = !cur;
    for (int i = 0; i <= K; ++i) {                                 // 枚举构成相似单词对数的 K 种情况
      f[cur][i] = f[!cur][i];                                      // 初始值由上一组单词的答案继承而来
      for (int j = 1; j <= rep && (((j - 1) * j) >> 1) <= i; ++j)  // 枚举组成的相似单词对数
        (f[cur][i] += (l64)f[!cur][i - (((j - 1) * j) >> 1)] * bin_coeff[rep][j] % MOD) %= MOD;
    }
  }

  std::cout << f[cur][K] << endl;
  fflush(stdout);
  return 0;
}
