#include <string>
#include <vector>
#include <iostream>

const int MAX_M = 25;

int N, M, MOD;
std::string pat;
int pi[MAX_M];

namespace VecMatrix {
  template <typename T>
  using Mat = std::vector<std::vector<T>>;

  template <typename T>
  void zeroify(Mat<T>& A, size_t R, size_t C) { A.assign(R, std::vector<int>(C, 0)); }

  template <typename T>
  void unitize(Mat<T>& A, size_t N) {
    zeroify(A, N, N);
    for (size_t i = 0; i < N; ++i) A[i][i] = 1;
  }

  template <typename T, typename bufT = size_t>
  Mat<T> mul(Mat<T> A, Mat<T> B, size_t N, size_t M, size_t P) {
    Mat<T> product;
    zeroify(product, N, P);
    for (size_t i = 0; i < N; ++i)
      for (size_t k = 0; k < P; ++k)
        for (size_t j = 0; j < M; ++j)
          product[i][k] = ((bufT)A[i][j] * B[j][k] + product[i][k]) % MOD;
    return product;
  }

  template <typename T, typename intT, typename bufT = size_t>
  Mat<T> power(Mat<T> a, intT k, size_t N) {
    Mat<T> result;
    unitize(result, N);
    while (k) {
      if (k & 1) result = mul<T, bufT>(result, a, N, N, N);
      a = mul<T, bufT>(a, a, N, N, N);
      k >>= 1;
    }
    return result;
  }
}  // namespace VecMatrix
using namespace VecMatrix;

Mat<int> A;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M >> MOD;
  std::cin >> pat;

  A.resize(M, std::vector<int>(M, 0));

  for (int i = 1, j = 0; i < M; ++i) {
    while (j > 0 && pat[i] != pat[j]) j = pi[j - 1];
    if (pat[i] == pat[j]) ++j;
    pi[i] = j;
  }

  for (int i = 0; i < M; ++i)
    for (int c = '0', p = i; c <= '9'; ++c, p = i) {
      while (p > 0 && c != pat[p]) p = pi[p - 1];
      if (c == pat[p]) ++p;
      if (p < M) ++A[i][p];
    }

  Mat<int> F = power(A, N, M);

  int ans = 0;
  for (int i = 0; i < M; ++i) ans = (ans + F[0][i]) % MOD;
  std::cout << ans << std::endl;

  return 0;
}
