#include <cstdio>
#include <cstring>

const int MAX_N = 1e5 + 5;
const int MAX_M = 2e5 + 5;

int N, S;
int ed[MAX_M], nx[MAX_M], wt[MAX_M], head[MAX_N], idx;
void connect(int u, int v, int w) { ed[idx] = v, wt[idx] = w, nx[idx] = head[u], head[u] = idx++; }

int dist[MAX_N];

void DFS(int u) {
  for (int i = head[u]; ~i; i = nx[i]) {
    int v = ed[i];
    if (~dist[v]) continue;
    dist[v] = dist[u] + wt[i];
    DFS(v);
  }
}

int main() {
  scanf("%d %d\n", &N, &S);
  memset(head, -1, sizeof(int) * (N + 1));

  int sumW = 0;

  for (int i = 1, u, v, w; i < N; ++i) {
    scanf("%d %d %d\n", &u, &v, &w);
    connect(u, v, w), sumW += w;
    connect(v, u, w), sumW += w;
  }

  memset(dist, -1, sizeof(int) * (N + 1));
  dist[1] = 0, DFS(1);

  int farthest = 0, distance = 0;

  for (int i = 1; i <= N; ++i)
    if (dist[i] > distance)
      farthest = i, distance = dist[i];

  memset(dist, -1, sizeof(int) * (N + 1));
  dist[farthest] = 0, DFS(farthest);

  distance = 0;
  for (int i = 1; i <= N; ++i)
    if (dist[i] > distance)
      distance = dist[i];

  printf("%d\n", sumW - distance);
  return 0;
}
