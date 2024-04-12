// 参考题解：https://www.luogu.com.cn/blog/pks-LOVING/solution-p1516

#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

int x, y, m, n, L;

int extend_gcd(int a, int b, i64 &x, i64 &y) {
    if (b == 0) return x = 1, y = 0, a;
    int d = extend_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> x >> y >> m >> n >> L;

    i64 xx = 0, yy = 0;
    int d = extend_gcd(m - n, L, xx, yy);  // 计算出方程的解并求得 gcd(x, y)

    if ((y - x) % d)  // 方程无解
        puts("Impossible");
    else {                      // 方程有解，但当前得出的 x 不一定是最小非负整数解
        xx = (y - x) / d * xx;  // 按比例扩大
        i64 t = abs(L / d);     // xx_min = xx mod (L / gcd(m - n, L))
        cout << (xx % t + t) % t << endl;
    }

    return fflush(stdout), 0;
}
