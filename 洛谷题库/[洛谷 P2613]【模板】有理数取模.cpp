#include <iostream>

const int MOD = 19260817;

template <typename T>
T read() {
  short int f = 1;
  T var = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -f;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') var = (var * 10 + ch - '0') % MOD, ch = getchar();
  return var * f;
}

void exgcd(int a, int b, int& x, int& y) {
  if (!b) return x = 1, y = 0, void();
  exgcd(b, a % b, y, x);
  y -= a / b * x;
}

int main() {
  int a = read<int>();
  int b = read<int>();

  if (!b)
    return std::cout << "Angry!" << std::endl, 0;

  int x = 0, y = 0;
  exgcd(b, MOD, x, y);
  x = (x % MOD + MOD) % MOD;

  std::cout << (long long)a * x % MOD << std::endl;
  return 0;
}
