#include <iostream>

#define endl '\n'

#ifdef _WIN32
#define putchar_unlocked _putchar_nolock
#endif

namespace FastIO {
    const int MAX_BUF = 1 << 20;
    char buf[MAX_BUF], *p1, *p2;

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)

    template <typename T>
    T read() {
        T x = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-') f = -f;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
        return x * f;
    }

    template <typename T>
    void write(T x) {
        if (x < 0) putchar_unlocked('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar_unlocked(x % 10 + '0');
    }
}  // namespace FastIO
using namespace FastIO;

const int MAX_N = 3e6 + 5;

int n, a[MAX_N], f[MAX_N];

struct Stack {
  int e[MAX_N], t;
  inline void push(int x) { e[++t] = x; }
  inline void pop() { t--; }
  inline int top() { return e[t]; }
  inline bool empty() { return !t; }
} st;

int main() {
  n = read<int>();
  for (int i = 1; i <= n; i++) a[i] = read<int>();

  for (int i = n; i > 0; i--) {
    while (!st.empty() && a[st.top()] <= a[i]) st.pop();
    if (st.empty()) f[i] = 0;
    else f[i] = st.top();
    st.push(i);
  }

  for (int i = 1; i <= n; i++)
    write(f[i]), putchar_unlocked(' ');
    
  putchar_unlocked('\n');
  return fflush(stdout), 0;
}
