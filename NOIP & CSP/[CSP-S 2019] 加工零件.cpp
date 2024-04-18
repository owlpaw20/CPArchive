#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
using PII = pair<int, int>;

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
      x = x * 10 + ch - 48, ch = getchar();
    return x * f;
  }
}  // namespace FastIO
using namespace FastIO;

const int N = 1e5 + 10;
const int M = 2e5 + 10;
const int INF = 0x3F3F3F3F;

int n, m, q, idx;
int ed[M], nx[M], head[N];
int dist[N][2];

void connect(int u, int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

void BFS(int st) {
  memset(dist, 0x3F, sizeof dist);
  queue<PII> q;
  dist[st][0] = 0;
  q.emplace(st, 0);
  while (!q.empty()) {
    PII u = q.front();
    q.pop();
    int ver = u.first, type = u.second;
    for (int i = head[ver]; ~i; i = nx[i]) {
      int j = ed[i];
      if (dist[j][type ^ 1] > dist[ver][type] + 1) {
        dist[j][type ^ 1] = dist[ver][type] + 1;
        q.emplace(j, type ^ 1);
      }
    }
  }
}

int main() {
  memset(head, -1, sizeof head);
  n = read(), m = read(), q = read();
  while (m--) {
    int u, v;
    u = read(), v = read();
    connect(u, v);
    connect(v, u);
  }
  BFS(1);
  while (q--) {
    int a, L;
    a = read(), L = read();
    if (a == 1 && head[1] == -1)
      puts("No");
    else if (dist[a][L & 1] <= L)
      puts("Yes");
    else
      puts("No");
  }
  return 0;
}
