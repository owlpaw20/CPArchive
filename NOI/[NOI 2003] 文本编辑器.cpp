#include <ext/rope>
#include <iostream>

#define endl '\n'

using __gnu_cxx::rope;

const int MAX_BUF = 2e6 + 5;

int q, pos;
char buf[MAX_BUF];

rope<char> tree;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> q;

  while (q--) {
    std::string type;
    std::cin >> type;

    if (type == "Move") {
      int x;
      std::cin >> x;
      pos = x;
    } else if (type == "Insert") {
      int i = 0, x;
      std::cin >> x;
      while (x) {
        buf[i] = std::cin.get();
        if (buf[i] >= 32 && buf[i] <= 126) ++i, --x;
      }
      buf[i] = '\0';
      tree.insert(pos, buf);
    } else if (type == "Delete") {
      int x;
      std::cin >> x;
      tree.erase(pos, x);
    } else if (type == "Get") {
      int x;
      std::cin >> x;
      std::cout << tree.substr(pos, x) << endl;
    } else
      type == "Prev" ? --pos : ++pos;
  }

  fflush(stdout);
  return 0;
}
