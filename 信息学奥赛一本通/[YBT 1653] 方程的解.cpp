// 隔板法的数学推导可见 https://www.acwing.com/solution/content/48085/

#pragma GCC optimize("O2,unroll-loops,inline")

#include <vector>
#include <iostream>
#include <algorithm>

using LL = long long;
using BigInt = std::vector<short>;

const int MOD = 1e3;
const int MAX_N = 1e3 + 5;
const int MAX_K = 1e2 + 5;

int K, X;
BigInt C[MAX_N][MAX_K];

template <typename intT>
intT power(intT b, intT e, intT mod) noexcept {
  intT res = 1;
  while (e) {
    ((e & 1) && (res = res * b % mod));
    b = b * b % mod;
    e >>= 1;
  }
  return res;
}

BigInt operator+(BigInt A, BigInt B) noexcept {
  if (A.size() < B.size()) std::swap(A, B);

  BigInt sum;
  int carry = 0;

  for (size_t i = 0; i < A.size(); ++i) {
    carry += A[i];
    if (i < B.size()) carry += B[i];
    sum.push_back(carry % 10), carry /= 10;
  }

  if (carry) sum.push_back(carry);
  return sum;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> K >> X;
  int N = power(X % MOD, X, MOD);

  for (int i = 0; i < N; ++i)
    for (int j = 0; j <= i && j < K; ++j)
      if (!j) C[i][j].push_back(1);
      else C[i][j] = C[i - 1][j] + C[i - 1][j - 1];

  BigInt ans = C[N - 1][K - 1];
  for (auto it = ans.rbegin(); it != ans.rend(); ++it) std::cout << *it;
  std::cout << std::endl;

  return 0;
}
