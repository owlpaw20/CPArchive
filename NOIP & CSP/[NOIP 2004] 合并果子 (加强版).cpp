#include <queue>
#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

namespace FastIO {
    i64 read() {
        i64 x = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-')
                f = -f;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9')
            x = x * 10 + ch - 48, ch = getchar();
        return x * f;
    }
    void write(i64 x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}  // namespace FastIO
using namespace FastIO;

const int N = 1e7 + 5;

int n;
int vis[N];
queue<i64> a, b;

int main() {
    n = read();
    for (int i = 1; i <= n; i++) vis[read()]++;

    for (int i = 1; i <= 1e5; i++)
        while (vis[i])
            a.push(i), vis[i]--;

    i64 ans = 0;

    for (int i = 1; i < n; i++) {
        i64 x, y;

        if (b.empty() || (!a.empty() && a.front() < b.front())) x = a.front(), a.pop();
        else x = b.front(), b.pop();
        if (b.empty() || (!a.empty() && a.front() < b.front())) y = a.front(), a.pop();
        else y = b.front(), b.pop();

        ans += x + y;
        b.push(x + y);
    }

    write(ans), putchar('\n');
    return fflush(stdout), 0;
}
