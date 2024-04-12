#include <cstring>
#include <iostream>

using namespace std;
using Long = long long;

const int N = 2e5 + 10;

namespace FastIO {
    int read() {
        int x = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-')
                f = -f;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9')
            x = x * 10 + (ch ^ 48), ch = getchar();
        return x * f;
    }
    Long read64() {
        Long x = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-')
                f = -f;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9')
            x = x * 10 + (ch ^ 48), ch = getchar();
        return x * f;
    }
    void write(int x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
    void write64(Long x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) write64(x / 10);
        putchar(x % 10 + '0');
    }
}  // namespace FastIO
using namespace FastIO;

Long n, sum[N], ans[N];

struct FenwickTree {
    Long c[N];
    Long lowbit(Long x) {
        return x & -x;
    }
    Long query(Long x) {
        Long ret = 0;
        for (Long i = x; i; i -= lowbit(i))
            ret += c[i];
        return ret;
    }
    void modify(Long x, Long delta) {
        for (Long i = x; i <= n; i += lowbit(i))
            c[i] += delta;
    }
    FenwickTree() {
        memset(c, 0, sizeof c);
    }
} tr;

int main() {
    n = read64();
    for (int i = 1; i <= n; i++) {
        sum[i] = read64();
        tr.modify(i, i);
    }
    for (int i = n; i >= 1; i--) {
        Long t = sum[i] + 1;
        Long l = 1, r = n;
        while (l < r) {
            Long mid = (l + r) >> 1;
            if (tr.query(mid) >= t)
                r = mid;
            else
                l = mid + 1;
        }
        ans[i] = r;
        tr.modify(r, -r);
    }
    for (int i = 1; i <= n; i++)
        write64(ans[i]), putchar(i == n ? '\n' : ' ');
    return 0;
}
