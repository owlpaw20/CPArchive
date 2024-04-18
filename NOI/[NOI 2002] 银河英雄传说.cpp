#include <iostream>

#define endl '\n'

using namespace std;

const int N = 3e4 + 10;
int t, p[N], cnt[N], dist[N];

int find(int x) {
  if (p[x] == x) return x;
  int k = p[x];
  p[x] = find(p[x]);
  dist[x] += dist[k];
  cnt[x] = cnt[p[x]];
  return p[x];
}

void merge(int x, int y) {
  int px = find(x), py = find(y);
  if (px != py) {
    p[px] = py;
    dist[px] = dist[py] + cnt[py];
    cnt[py] += cnt[px];
    cnt[px] = cnt[py];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  for (int i = 1; i <= 30000; i++)
    p[i] = i, cnt[i] = 1;

  cin >> t;

  while (t--) {
    char opt;
    int i, j;
    cin >> opt >> i >> j;

    if (opt == 'M')
      merge(i, j);
    else if (opt == 'C') {
      int pi = find(i), pj = find(j);
      if (pi == pj)
        cout << abs(dist[i] - dist[j]) - 1 << endl;
      else
        cout << -1 << endl;
    }
  }

  fflush(stdout);
  return 0;
}
