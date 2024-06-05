#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;
using Matrix = vector<vector<int>>;

const int MOD = 1e9 + 7;

int n, p, m;
Matrix A, B;

Matrix operator*(const Matrix &A, const Matrix &B) {
  Matrix ret(n, vector<int>(m, 0));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < p; j++)
      for (int k = 0; k < m; k++)
        ret[i][k] = (((i64)ret[i][k] + (i64)A[i][j] * B[j][k]) % MOD + MOD) % MOD;
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> p >> m;
  A.resize(n, vector<int>(p, 0));
  B.resize(p, vector<int>(m, 0));

  for (vector<int> &row : A)
    for (int &num : row)
      cin >> num;

  for (vector<int> &row : B)
    for (int &num : row)
      cin >> num;

  Matrix C = A * B;

  for (vector<int> row : C) {
    for (int num : row)
      cout << num << ' ';
    cout << endl;
  }

  return fflush(stdout), 0;
}
