#include <iostream>

#define endl '\n'

using namespace std;

const int N = 2e2 + 10;

int len, wid, hgt;
bool cube[N][N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> len >> wid >> hgt;
  for (int x = 1; x <= hgt; x++)
    for (int y = 1; y <= len; y++)
      for (int z = 1; z <= wid; z++)
        cin >> cube[y][z][x];

  for (int z = hgt; z >= 1; z--) {
    for (int x = 1; x <= len; x++) {
      bool flag = 0;
      for (int y = 1; y <= wid; y++)
        if (cube[x][y][z]) {
          flag = 1;
          break;
        }
      if (flag)
        cout << 1 << " ";
      else
        cout << 0 << " ";
    }
    cout << endl;
  }

  for (int z = hgt; z >= 1; z--) {
    for (int y = wid; y >= 1; y--) {
      bool flag = 0;
      for (int x = 1; x <= len; x++)
        if (cube[x][y][z]) {
          flag = 1;
          break;
        }
      if (flag)
        cout << 1 << " ";
      else
        cout << 0 << " ";
    }
    cout << endl;
  }

  for (int y = wid; y >= 1; y--) {
    for (int x = 1; x <= len; x++) {
      bool flag = 0;
      for (int z = hgt; z >= 1; z--)
        if (cube[x][y][z]) {
          flag = 1;
          break;
        }
      if (flag)
        cout << 1 << " ";
      else
        cout << 0 << " ";
    }
    cout << endl;
  }

  fflush(stdout);
  return 0;
}
