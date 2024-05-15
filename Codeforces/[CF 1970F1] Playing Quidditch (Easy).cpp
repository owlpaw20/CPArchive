#pragma GCC optimize("O2,unroll-loops,inline")

#include <map>
#include <string>
#include <iostream>

using PII = std::pair<int, int>;
using PCC = std::pair<char, char>;

const int MAX_N = 1e2 + 5;

int N, M, r, b;
std::map<PCC, PII> player;
char goals[MAX_N][MAX_N];

void check_goal(int x, int y, int t) {
  if (!goals[x][y]) return;
  std::cout << t << (goals[x][y] == 'R' ? " BLUE GOAL" : " RED GOAL") << '\n';
  goals[x][y] == 'R' ? ++b : ++r;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= M; ++j) {
      char a, b;
      std::cin >> a >> b;

      if (a == 'R') {
        if (isdigit(b)) player.emplace(PCC(a, b), PII(i, j));
        else goals[i][j] = a;
      } else if (a == 'B') {
        if (isdigit(b)) player.emplace(PCC(a, b), PII(i, j));
        else goals[i][j] = a;
      }
    }

  int T;
  std::cin >> T;
  for (int t = 0; t < T; ++t) {
    char a, b, type;
    std::cin >> a >> b >> type;

    PCC p(a, b);

    if (type == 'U') player[p].first -= 1;
    else if (type == 'D') player[p].first += 1;
    else if (type == 'L') player[p].second -= 1;
    else if (type == 'R') player[p].second += 1;
    else if (type == 'T') check_goal(player[p].first, player[p].second, t);
    else std::cin >> a >> b;
  }

  std::cout << "FINAL SCORE: " << r << ' ' << b << std::endl;
  return 0;
}
