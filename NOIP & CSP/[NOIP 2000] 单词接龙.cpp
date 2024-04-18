#include <string>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 25;

int n;
int ans;
char st;
int vis[N];
string w[N];
int len[N][N];

// 对字符串接龙进行深搜
void DFS(string x, int prev) {
  ans = max((int)x.size(), ans);
  for (int i = 1; i <= n; i++)
    if (len[prev][i] != 0 && vis[i] < 2) {
      vis[i] += 1;
      DFS(x + w[i].substr(len[prev][i]), i);
      vis[i] -= 1;
    }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> w[i];
  cin >> st;

  // 预处理出每对字符串的最长相等真前后缀
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      string a = w[i], b = w[j];
      for (int k = 1; k < (int)min(a.size(), b.size()); k++)
        if (a.substr(a.size() - k, k) == b.substr(0, k)) {
          len[i][j] = k;
          break;
        }
    }

  for (int i = 1; i <= n; i++)
    if (w[i].front() == st)
      vis[i] += 1, DFS(w[i], i), vis[i] -= 1;

  cout << ans << endl;
  fflush(stdout);
  return 0;
}
