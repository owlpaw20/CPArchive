#include <cstring>
#include <iostream>

const int MAX_N = 30;
const int MAX_L = 3;

int N;
int map[MAX_N];
char eq[MAX_L][MAX_N];
bool used[MAX_N];

void DFS(int d, int r, int carry) {
  if (!d) {        // 如果已经枚举完了所有数字位
    if (!carry) {  // 如果仍存在进位则不合法 (因为得数与两个加数长度相同) 否则输出合法结果
      for (int i = 0; i < N; ++i) std::cout << map[i] << ' ';
      std::cout << std::endl;
      exit(0);
    }
    return;
  }

  // 剪枝
  for (int i = d - 1, a, b, c; i; --i)  // 考虑尚未枚举的所有数位
    if ((a = map[eq[0][i] - 'A']) != -1 &&
        (b = map[eq[1][i] - 'A']) != -1 &&
        (c = map[eq[2][i] - 'A']) != -1 &&         // 如果三个数位都已经确定
        (a + b) % N != c && (a + b + 1) % N != c)  // 但是无论是否进位都不相符合
      return;                                      // 则剪掉该不合法枝条

  // 考虑当前位
  if (map[eq[r][d] - 'A'] == -1) {  // 如果当前位的字母还没有对应的数字
    for (int i = N - 1; ~i; --i)    // 则从大到小枚举所有未被占用的取值 (更有利于提前确定最高位的进位情况，从而提早剪掉不合法的方案)
      if (!used[i]) {
        if (r != 2) {  // 如果当前位于加数行
          map[eq[r][d] - 'A'] = i;
          used[i] = true;
          DFS(d, r + 1, carry);
          used[i] = false;
          map[eq[r][d] - 'A'] = -1;
        } else {  // 如果当前位于得数行
          int res = map[eq[0][d] - 'A'] + map[eq[1][d] - 'A'] + carry;
          if (i != res % N) continue;  // 如果当前枚举到的数字与得数不匹配，则跳过
          map[eq[2][d] - 'A'] = i;
          used[i] = true;
          DFS(d - 1, 0, res / N);
          used[i] = false;
          map[eq[2][d] - 'A'] = -1;
        }
      }
  }

  // 如果当前位的字母已经有了对应的数字
  else {
    if (r != 2)  // 如果位于加数行
      DFS(d, r + 1, carry);
    else {  // 如果位于得数行
      int res = map[eq[0][d] - 'A'] + map[eq[1][d] - 'A'] + carry;
      if (map[eq[2][d] - 'A'] != res % N) return;
      DFS(d - 1, 0, res / N);
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  memset(map, -1, sizeof(int) * (N + 1));

  for (int i = 0; i < 3; ++i)
    for (int j = 1; j <= N; ++j)
      std::cin >> eq[i][j];

  DFS(N, 0, 0);  // 从低位开始枚举
  return 0;
}
