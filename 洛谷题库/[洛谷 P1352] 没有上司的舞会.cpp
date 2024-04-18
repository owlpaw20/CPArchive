#include <iostream>

#define endl '\n'

using namespace std;

const int N = 6e3 + 10;

int n, a[N], ver[N], Next[N], head[N], tot;
int f[N][2], x, y;
bool is_child[N];

void add(int x, int y) {
  tot++;
  ver[tot] = y;
  Next[tot] = head[x];
  head[x] = tot;
}

void dp(int x) {
  f[x][0] = 0;
  f[x][1] = a[x];
  for (int i = head[x]; i; i = Next[i]) {
    int y = ver[i];
    dp(y);
    f[x][0] += max(f[y][0], f[y][1]);
    f[x][1] += f[y][0];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];

  for (int i = 1; i < n; i++) {
    cin >> x >> y;
    add(y, x);
    is_child[x] = 1;
  }

  for (int i = 1; i <= n; i++)
    if (!is_child[i]) {
      dp(i);
      cout << max(f[i][0], f[i][1]) << endl;
      return 0;
    }

  fflush(stdout);
  return 0;
}
