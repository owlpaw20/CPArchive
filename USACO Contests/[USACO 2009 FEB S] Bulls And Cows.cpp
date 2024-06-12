#include <iostream>

const int MAX_N = 1e5 + 5;
const int MOD = 5e6 + 11;

int N, K, f[MAX_N];  // f[i] 表示 i 头牛站成一排的方法数

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> K;

  for (int i = 1; i <= K + 1; ++i)  // 对于前 K + 1 头牛
    f[i] = i + 1;                   // 要么全部都是奶牛，要么某一个位置上是公牛

  for (int i = K + 2; i <= N; ++i) {    // 对于后面的牛
    f[i] = f[i - 1] + f[i - K - 1];     // 如果是奶牛，那么前面的牛没有任何要求
    (f[i] >= MOD) ? (f[i] -= MOD) : 0;  // 如果是公牛，那么前面 K 头牛可以确定为全部是奶牛
  }

  std::cout << f[N] << std::endl;

  return 0;
}
