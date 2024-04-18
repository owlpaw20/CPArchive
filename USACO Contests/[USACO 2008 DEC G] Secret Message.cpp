#include <cstring>
#include <iostream>

using namespace std;

const int N = 5e5 + 10;

int n, m, idx, trie[N][2];
int ed[N], vis[N];

void insert(int arr[], int len) {
  int p = 0;
  for (int i = 0; i < len; i++) {
    int c = arr[i];
    if (trie[p][c] == -1) trie[p][c] = ++idx;
    p = trie[p][c];
    vis[p]++;
  }
  ed[p]++;
}

int find(int arr[], int len) {
  int p = 0, res = 0;
  for (int i = 0; i < len; i++) {
    int c = arr[i];
    if (trie[p][c] == -1) return res;
    p = trie[p][c];
    res += ed[p];
  }
  return res - ed[p] + vis[p];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> m >> n;
  memset(trie, -1, sizeof trie);

  while (m--) {
    int t;
    cin >> t;
    int c[t + 10] = {0};
    for (int i = 0; i < t; i++)
      cin >> c[i];
    insert(c, t);
  }

  while (n--) {
    int t;
    cin >> t;
    int c[t + 10] = {0};
    for (int i = 0; i < t; i++)
      cin >> c[i];
    cout << find(c, t) << endl;
  }

  return 0;
}