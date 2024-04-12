#include <cmath>
#include <iostream>

#define endl '\n'

using namespace std;
using f64 = double;  // 学 Rust 语言学的

const int N = 1e5 + 5;
const f64 EPS = 1e-6;  // 题目规定：当两实数之差小于等于 1e-6 时，认为他们相等

int n;
int a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    f64 l = -1e9 - 5;  // 左边界初始值
    f64 r = 1e9 + 5;   // 右边界初始值
    bool failed = false;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i == 1) continue;

        if (failed) continue;                            // 如果已经无解就不用继续算了
        if (a[i] == a[i - 1]) failed = true;             // 如果有相同元素就一定无解
        if (l > r || fabs(r - l) <= EPS) failed = true;  // 如果左边界已经超过右边界就一定无解

        if (a[i - 1] < a[i]) r = min(r, (a[i - 1] + a[i]) / 2.0);  // 更新右边界
        if (a[i - 1] > a[i]) l = max(l, (a[i - 1] + a[i]) / 2.0);  // 更新左边界
    }

    if (l > r || fabs(r - l) <= EPS) failed = true;

    if (failed)
        puts("pigeon");
    else {
        f64 mid = (l + r) / 2.0;  // 其实可以在区间内随便取的
        puts("lovely");           // lovely pigeon
        printf("%.7lf\n", mid);
    }

    return fflush(stdout), 0;
}
