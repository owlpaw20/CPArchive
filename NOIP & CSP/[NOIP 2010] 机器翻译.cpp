#include <queue>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e3 + 10;

int m, n;
bool vis[N];
queue<int> mem;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> m >> n;

  int ans = 0;

  while (n--) {
    int word;
    cin >> word;

    if (vis[word]) continue;

    if ((int)mem.size() >= m) {
      int buf = mem.front();
      mem.pop();
      vis[buf] = false;
    }

    mem.push(word);
    vis[word] = true;
    ans++;
  }

  cout << ans << endl;
  fflush(stdout);
  return 0;
}
