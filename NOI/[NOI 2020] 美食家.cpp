#include <array>
#include <tuple>
#include <iostream>
#include <algorithm>

#define endl '\n'

using i64 = long long int;
using TUP = std::tuple<int, int, int>;

const int MAX_N = 55;
const int MAX_LG_T = 35;
const int MAX_M = 5e2 + 5;
const int MAX_K = 2e2 + 5;
const int MAX_N_S = MAX_N * 5;

const i64 I64_MIN = 0xC0C0C0C0C0C0C0C0;

struct Matrix {
  i64 data[MAX_N_S][MAX_N_S];
  int row, col;

  inline void fill(const i64 x) {
    for (int i = 1; i <= row; ++i)
      for (int j = 1; j <= col; ++j)
        data[i][j] = x;
  }

  inline Matrix operator*(const Matrix& B) const {
    Matrix C(row, B.col, I64_MIN);
    for (int i = 1; i <= row; ++i)
      for (int j = 1; j <= col; ++j)
        for (int k = 1; k <= B.col; ++k)
          C.data[i][k] = std::max(C.data[i][k], data[i][j] + B.data[j][k]);
    return C;
  }

  Matrix() {}
  Matrix(const int _r, const int _c, const i64 x) : row(_r), col(_c) { fill(x); }
};

int n, m, T, K;
int c[MAX_N], logT;

TUP fest[MAX_K];
Matrix G, pow2[MAX_LG_T], vec;

// 预处理初始转移矩阵的 2 的某次幂次幂
void prep() {
  pow2[0] = G;
  for (int i = 1; i <= logT; ++i)
    pow2[i] = pow2[i - 1] * pow2[i - 1];
}

inline void power(Matrix& A, int b) {
  if (b == 0) return;
  for (int i = 0; i <= logT; ++i)
    if ((b >> i) & 1) A = pow2[i] * A;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m >> T >> K;

  logT = std::__lg(T);
  G = Matrix(n * 5, n * 5, I64_MIN);

  for (int i = 1; i <= n; ++i)
    for (int w = 1; w < 5; ++w)
      G.data[n * w + i][n * (w - 1) + i] = 0;

  // 读入部分
  for (int i = 1; i <= n; ++i) std::cin >> c[i];

  for (int i = 1, u, v, w; i <= m; ++i) {
    std::cin >> u >> v >> w;
    G.data[v][n * (w - 1) + u] = c[u];
  }

  for (int i = 1; i <= K; ++i) {
    auto& [t, x, y] = fest[i];
    std::cin >> t >> x >> y;
  }

  // 基于得出的转移矩阵进行预处理
  prep();

  // 对所有美食节按照时间顺序排序
  std::sort(fest + 1, fest + K + 1);

  Matrix vec(n * 5, 1, I64_MIN);
  vec.data[1][1] = 0;

  // 预处理所有美食节按照时间顺序转移之后的结果
  int current_time = 0;

  for (int i = 1; i <= K; ++i) {
    auto [time, city, joy] = fest[i];
    power(vec, time - current_time);
    vec.data[city][1] += joy;
    current_time = time;
  }

  power(vec, T - current_time);

  i64 ans = vec.data[1][1] + c[1];
  std::cout << (ans < 0 ? -1 : ans) << endl;
  return fflush(stdout), 0;
}
