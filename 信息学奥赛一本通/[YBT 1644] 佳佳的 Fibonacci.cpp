#pragma GCC optimize("O2,unroll-loops,inline")

#include <array>
#include <iostream>

using LL = long long;

int N, MOD;

namespace Matrix {
  template <typename T, size_t R, size_t C>
  using Mat = std::array<std::array<T, C>, R>;

  template <typename T, size_t R, size_t C>
  void zeroify(Mat<T, R, C>& A) {
    for (size_t i = 0; i < R; ++i)
      for (size_t j = 0; j < C; ++j)
        A[i][j] = 0;
  }

  template <typename T, size_t N>
  void unitize(Mat<T, N, N>& A) {
    zeroify(A);
    for (size_t i = 0; i < N; ++i) A[i][i] = 1;
  }

  template <typename T, size_t N, size_t M, size_t P, typename bufT = size_t>
  Mat<T, N, P> operator*(Mat<T, N, M> A, Mat<T, M, P> B) {
    Mat<T, N, P> product;
    zeroify(product);
    for (size_t i = 0; i < N; ++i)
      for (size_t k = 0; k < P; ++k)
        for (size_t j = 0; j < M; ++j)
          product[i][k] = ((bufT)A[i][j] * B[j][k] + product[i][k]) % MOD;
    return product;
  }

  template <typename T, size_t N>
  Mat<T, N, N> operator^(Mat<T, N, N> a, int k) {
    Mat<T, N, N> result;
    unitize(result);
    while (k) {
      if (k & 1) result = result * a;
      a = a * a;
      k >>= 1;
    }
    return result;
  }
}  // namespace Matrix
using namespace Matrix;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> MOD;

  Mat<int, 1, 4> F_1 = {1, 1, 1, 0};
  Mat<int, 4, 4> BASE = {{{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}}};
  Mat<int, 4, 4> MUL = BASE ^ (N - 1);
  Mat<int, 1, 4> F_n = F_1 * MUL;

  std::cout << (((LL)N * F_n[0][2] - F_n[0][3]) % MOD + MOD) % MOD << std::endl;
  return 0;
}
