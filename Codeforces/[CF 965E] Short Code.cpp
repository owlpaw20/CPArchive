#include <string>
#include <iostream>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>

namespace pbds = __gnu_pbds;

const int MAX_N = 1e5 + 5;

int N;

int tr[MAX_N][26], idx, ans;
bool flag[MAX_N];

pbds::priority_queue<int> heap[MAX_N];

void ins(std::string s) {
  int p = 0, len = s.length();
  for (int i = 0, c; i < len; ++i) {
    c = s[i] - 'a';
    if (!tr[p][c]) tr[p][c] = ++idx;
    p = tr[p][c];
  }

  flag[p] = true;
  heap[p].push(len);
  ans += len;
}

void DFS(int u = 0, int depth = 0) {
  for (int i = 0, v; i < 26; ++i)
    if ((v = tr[u][i]))
      DFS(v, depth + 1), heap[u].join(heap[v]);

  if (u && !flag[u]) {
    ans -= heap[u].top() - depth;
    heap[u].pop();
    heap[u].push(depth);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  for (int i = 1; i <= N; ++i) {
    static std::string s;
    std::cin >> s;
    ins(s);
  }

  DFS();

  std::cout << ans << std::endl;
  return 0;
}
