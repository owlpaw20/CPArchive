#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 1e5 + 5;
const int MAX_3N = MAX_N * 3;

int N, M, idx;
std::map<std::string, int> map;

std::string tolower(std::string s) {
  for (char& ch : s) ch = tolower(ch);
  return s;
}

int loc[MAX_3N], cnt[MAX_3N], len[MAX_3N];
std::vector<std::vector<int>> gg;

int dfn[MAX_3N], low[MAX_3N], ts;
int bel[MAX_3N], scc;
std::stack<int> stk;
bool instk[MAX_3N];

int f[MAX_3N], g[MAX_3N];

void Tarjan(int u) {
  dfn[u] = low[u] = ++ts;
  stk.push(u), instk[u] = true;

  for (int v : gg[u])
    if (!dfn[v]) {
      Tarjan(v);
      low[u] = std::min(low[u], low[v]);
    } else if (instk[v])
      low[u] = std::min(low[u], dfn[v]);

  if (low[u] == dfn[u]) {
    ++scc;
    int x = 0;

    while (x != u) {
      x = stk.top(), stk.pop();
      instk[x] = false;
      bel[x] = scc;

      if (f[scc] > cnt[x]) f[scc] = cnt[x], g[scc] = len[x];
      else if (f[scc] == cnt[x] && g[scc] > len[x]) g[scc] = len[x];
    }
  }
}

std::vector<std::vector<int>> gh;
bool vis[MAX_3N];

void DFS(int u) {
  if (vis[u]) return;
  vis[u] = true;

  for (int v : gh[u]) {
    DFS(v);
    if (f[u] > f[v]) f[u] = f[v], g[u] = g[v];
    else if (f[u] == f[v] && g[u] > g[v]) g[u] = g[v];
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  for (int i = 1; i <= N; ++i) {
    static std::string s;
    std::cin >> s, s = tolower(s);

    if (!map.count(s)) {
      int cntt = 0;
      for (char ch : s) cntt += ch == 'r';
      map[s] = ++idx, cnt[idx] = cntt, len[idx] = s.length();
    }

    loc[i] = map[s];
  }

  std::cin >> M;
  gg.resize(N + M * 2 + 1);

  while (M--) {
    static std::string s1, s2;
    std::cin >> s1 >> s2, s1 = tolower(s1), s2 = tolower(s2);

    if (!map.count(s1)) {
      int cnt1 = 0;
      for (char ch : s1) cnt1 += ch == 'r';
      map[s1] = ++idx, cnt[idx] = cnt1, len[idx] = s1.length();
    }

    if (!map.count(s2)) {
      int cnt2 = 0;
      for (char ch : s2) cnt2 += ch == 'r';
      map[s2] = ++idx, cnt[idx] = cnt2, len[idx] = s2.length();
    }

    gg[map[s1]].push_back(map[s2]);
  }

  memset(f, 0x3F, sizeof(int) * (idx + 1));
  memset(g, 0x3F, sizeof(int) * (idx + 1));

  for (int i = 1; i <= idx; ++i)
    if (!dfn[i])
      Tarjan(i);

  gh.resize(scc + 1);

  for (int i = 1; i <= idx; ++i)
    for (int v : gg[i])
      if (bel[i] != bel[v])
        gh[bel[i]].push_back(bel[v]);

  for (int i = 1; i <= scc; ++i) DFS(i);

  i64 ans1 = 0, ans2 = 0;
  for (int i = 1; i <= N; ++i) ans1 += f[bel[loc[i]]], ans2 += g[bel[loc[i]]];

  std::cout << ans1 << ' ' << ans2 << std::flush;
  return 0;
}
