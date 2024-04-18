#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
// 2 * 3 * 5 * ... * 23 * 29 > 2e9

int n, ans, max_factor_cnt;

/*  `prime_idx` 为当前使用的质因子在质因子数组中的下标
    `factor_cnt` 为当前数字的因数个数
    `exp` 为当前质因子的指数上限
    `num` 为当前数字的值 */
void DFS(int prime_idx, int factor_cnt, int exp, int num) {
  if (factor_cnt > max_factor_cnt ||                // 如果有因数更多的数
      (factor_cnt == max_factor_cnt && num < ans))  // 或者因数个数相同但值更小的数
    max_factor_cnt = factor_cnt, ans = num;         // 就更新答案

  if (prime_idx == 9) return;

  // 遍历当前质因子取多少为指数，确保指数不单增
  for (int i = 1; i <= exp; i++) {
    if ((i64)num * primes[prime_idx] > n) break;
    num *= primes[prime_idx];  // 计算再乘上质因子之后的数
    DFS(prime_idx + 1, factor_cnt * (i + 1), exp, num);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  DFS(0, 1, 30, 1);

  cout << ans << endl;
  fflush(stdout);
  return 0;
}
