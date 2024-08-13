#include <iostream>

const int MAX_N = 55;

int N, M, x, y;
char map[MAX_N][MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M >> x >> y;

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= M; ++j)
      std::cin >> map[i][j];

  std::string oper;
  std::cin >> oper;

  for (char ch : oper)
    if (ch == 'L' && y - 1 >= 1 && map[x][y - 1] == '.') y -= 1;
    else if (ch == 'R' && y + 1 <= M && map[x][y + 1] == '.') y += 1;
    else if (ch == 'D' && x + 1 <= N && map[x + 1][y] == '.') x += 1;
    else if (ch == 'U' && x - 1 >= 1 && map[x - 1][y] == '.') x -= 1;

  std::cout << x << ' ' << y << std::endl;
  return 0;
}
