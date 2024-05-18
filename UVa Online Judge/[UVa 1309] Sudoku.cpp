#include <cstring>
#include <iostream>

const int MAX_N = (1 << 22) + 1;

int g[16][16];
int choice[MAX_N];

struct {
  int head[MAX_N], size[MAX_N];
  int row[MAX_N], col[MAX_N];
  int ptr;

  struct {
    int l, r, u, d;
  } e[MAX_N];

  void init(int c) {
    for (int i = 0; i <= c; ++i) {
      e[i].l = i - 1, e[i].r = i + 1;
      e[i].u = e[i].d = i;
    }

    e[0].l = c, e[c].r = 0, ptr = c;

    memset(head, -1, sizeof head);
    memset(size, 0, sizeof size);
  }

  void insert(int r, int c) {
    row[++ptr] = r, col[ptr] = c, ++size[c];
    e[ptr].d = e[c].d, e[e[c].d].u = ptr;
    e[ptr].u = c, e[c].d = ptr;

    if (head[r] == -1)
      head[r] = e[ptr].l = e[ptr].r = ptr;
    else {
      e[ptr].r = e[head[r]].r, e[e[head[r]].r].l = ptr;
      e[ptr].l = head[r], e[head[r]].r = ptr;
    }
  }

  void remove(int c) {
    e[e[c].r].l = e[c].l, e[e[c].l].r = e[c].r;
    for (int i = e[c].d; i != c; i = e[i].d)
      for (int j = e[i].r; j != i; j = e[j].r)
        e[e[j].d].u = e[j].u, e[e[j].u].d = e[j].d, --size[col[j]];
  }

  void restore(int c) {
    for (int i = e[c].u; i != c; i = e[i].u)
      for (int j = e[i].l; j != i; j = e[j].l)
        e[e[j].d].u = e[e[j].u].d = j, ++size[col[j]];
    e[e[c].r].l = e[e[c].l].r = c;
  }

  bool solve(int depth = 0) {
    if (!e[0].r) {
      for (int i = 0, x, y, z; i < depth; ++i) {
        x = (choice[i] - 1) / 256;
        y = (choice[i] - 1) / 16 % 16;
        z = choice[i] % 16;
        if (z == 0) z = 16;
        g[x][y] = z;
      }
      return true;
    }

    int c = e[0].r;
    for (int i = e[0].r; i != 0; i = e[i].r)
      if (size[i] < size[c])
        c = i;

    remove(c);

    for (int i = e[c].d; i != c; i = e[i].d) {
      choice[depth] = row[i];
      for (int j = e[i].r; j != i; j = e[j].r) remove(col[j]);
      if (solve(depth + 1)) return true;
      for (int j = e[i].l; j != i; j = e[j].l) restore(col[j]);
    }

    restore(c);
    return false;
  }
} DLX;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int CASE = 0;

  do {
    if (std::cin.peek() == 10) std::cin.get();
    if (std::cin.peek() == EOF) break;
    if (CASE++) std::cout.put('\n');

    DLX.init(1024);

    for (int i = 0; i < 16; ++i)
      for (int j = 0; j < 16; ++j) {
        char ch;
        std::cin >> ch;

        g[i][j] = ch == '-' ? 0 : ch - 'A' + 1;

        for (int k = 1; k <= 16; ++k) {
          if (g[i][j] != k && g[i][j] != 0) continue;
          int t = i * 256 + j * 16 + k;
          DLX.insert(t, i * 16 + j + 1);
          DLX.insert(t, i * 16 + 256 + k);
          DLX.insert(t, j * 16 + 512 + k);
          DLX.insert(t, 768 + (i / 4 * 4 + j / 4) * 16 + k);
        }
      }

    DLX.solve();

    for (int i = 0; i < 16; ++i) {
      for (int j = 0; j < 16; ++j)
        std::cout.put(g[i][j] + 'A' - 1);
      std::cout.put('\n');
    }
  } while (true);

  return fflush(stdout), 0;
}
