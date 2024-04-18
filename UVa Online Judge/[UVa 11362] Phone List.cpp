#include <string>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int t, n, idx, trie[N][10], cnt[N];
string s[N];

void insert(string s) {
  int p = 0, len = s.size();
  for (int i = 0; i < len; i++) {
    int c = s[i] - '0';
    if (trie[p][c] == 0) trie[p][c] = ++idx;
    p = trie[p][c];
    cnt[p]++;
  }
}

bool find(string s) {
  int p = 0, len = s.size();
  for (int i = 0; i < len; i++) {
    int c = s[i] - '0';
    if (trie[p][c] == 0) return 0;
    p = trie[p][c];
  }
  return (cnt[p] - 1);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> t;
  while (t--) {
    int n;
    idx = 0;
    memset(trie, 0, sizeof trie);
    memset(cnt, 0, sizeof cnt);
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> s[i];
      insert(s[i]);
    }
    bool flag = false;
    for (int i = 0; i < n; i++) {
      flag = find(s[i]);
      if (flag) break;
    }
    if (flag)
      puts("NO");
    else
      puts("YES");
  }
  return 0;
}
