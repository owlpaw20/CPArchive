#include <cstring>
#include <iostream>

#define endl '\n'

using i64 = int64_t;
using PII = std::pair<int, int>;

const int MAX_N = 5e5 + 5;

int N;
char ch[MAX_N];
int fail[MAX_N];  // 根节点到当前节点所在路径上上一个未被匹配的左括号所在节点
i64 f[MAX_N];     // f[i] = 以节点 i 为结尾的合法括号串的数量

int ed[MAX_N], nx[MAX_N], head[MAX_N], idx;
int fa[MAX_N];

void connect(int u, int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

void DFS(const int u = 1) {
  fail[u] = fail[fa[u]];  // 当前节点为右括号时，暂时继承父节点的值准备转移

  if (ch[u] == '(')               // 当前节点为左括号时
    fail[u] = u;                  // 根据定义，fail[u] = u
  else if (fail[u]) {             // 当前节点为右括号且此前存在未匹配的节点时
    f[u] = f[fa[fail[u]]] + 1;    // 则 f[当前节点] <- f[最近未匹配节点的父节点] + 1
    fail[u] = fail[fa[fail[u]]];  // fail[当前节点] <- fail[最近未匹配节点的父节点]
  }

  for (int i = head[u]; ~i; i = nx[i]) DFS(ed[i]);
}

int main() {
  // freopen("brackets.in", "r", stdin);
  // freopen("brackets.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  memset(head, -1, sizeof head);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> ch[i];

  for (int i = 2; i <= N; ++i) {
    std::cin >> fa[i];
    connect(fa[i], i);
  }

  DFS();

  i64 ans = 0;
  for (i64 i = 1; i <= N; ++i)
    f[i] += f[fa[i]], ans ^= (i * f[i]);

  std::cout << ans << endl;

  return fflush(stdout), 0;
}
