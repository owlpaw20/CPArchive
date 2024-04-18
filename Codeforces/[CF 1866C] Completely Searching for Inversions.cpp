#include <vector>
#include <iostream>
using namespace std;
using i64 = long long;

namespace FastIO {
  int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-')
        f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
      x = x * 10 + (ch ^ 48), ch = getchar();
    return x * f;
  }
  void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
  }
}  // namespace FastIO
using namespace FastIO;

struct Edges {
  int v, w;
  Edges(int x, int y) : v(x), w(y) {}
};

const int N = 1e5 + 10;
const int MOD = 998244353;

bool vis[N];
int n, t, x, y;
int zero[N], one[N], f[N];
vector<Edges> ver[N];

void DFS(int u) {
  vis[u] = true;
  for (Edges i : ver[u]) {
    int v = i.v, w = i.w;
    if (w == 0) {
      f[u] = (f[u] + one[u]) % MOD;
      zero[u]++;
    } else if (w == 1)
      one[u]++;
    if (!vis[v]) DFS(v);
    f[u] = (f[u] + f[v]) % MOD;
    f[u] = (f[u] + (i64)zero[v] * one[u] % MOD) % MOD;
    zero[u] = (zero[u] + zero[v]) % MOD;
    one[u] = (one[u] + one[v]) % MOD;
  }
}

int main() {
  n = read();
  for (int i = 1; i <= n; i++) {
    t = read();
    for (int j = 1; j <= t; j++) {
      x = read(), y = read();
      ver[i].emplace_back((Edges){
        x, y});
    }
  }
  DFS(1);
  cout << f[1] << endl;
  return 0;
}
