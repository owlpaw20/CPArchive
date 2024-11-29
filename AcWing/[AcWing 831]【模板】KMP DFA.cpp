#include <bits/stdc++.h>

const int MAX_N = 100'005;

int N, M;
std::string P, S;
int kmp[MAX_N][70];

int convert(char c) {
  if (islower(c)) return c - 'a';
  if (isupper(c)) return c - 'A' + 26;
  if (isdigit(c)) return c - '0' + 52;
  return 62;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> P;

  kmp[0][convert(P[0])] = 1;
  P.push_back('\0');

  for (int i = 1, j = 0; i <= N; ++i) {
    for (int c = 0; c <= 62; ++c) kmp[i][c] = kmp[j][c];
    kmp[i][convert(P[i])] = i + 1;
    j = kmp[j][convert(P[i])];
  }

  std::cin >> M >> S;

  for (int i = 0, j = 0; i < M; ++i) {
    j = kmp[j][convert(S[i])];
    if (j == N) std::cout << i - N + 1 << ' ';
  }

  return 0;
}
