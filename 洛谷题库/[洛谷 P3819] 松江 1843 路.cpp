#include <iostream>
#include <algorithm>
#define endl '\n'

using namespace std;
using i64 = long long;
using PII = pair<i64, i64>;

const int N = 1e5 + 5;

i64 L, n, slope, intcp;
PII h[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> L >> n;
    for (int i = 1; i <= n; i++)
        cin >> h[i].first >> h[i].second;
    sort(h + 1, h + n + 1);

    // 计算函数第一段的斜率与 y 轴截距
    for (int i = 1; i <= n; i++) {
        slope -= h[i].second;
        intcp += h[i].first * h[i].second;
    }

    // 函数最小值的初始值
    i64 fval = slope * h[1].first + intcp;

    // 计算函数其他段的斜率与 y 轴截距，取得最小值
    h[n + 1].first = L;
    for (int i = 1; i <= n; i++) {
        slope += 2 * h[i].second;
        intcp -= 2 * h[i].first * h[i].second;
        i64 tval = slope * h[i + 1].first + intcp;
        if (tval > 0)
            fval = min(fval, tval);
    }

    cout << fval << endl;
    fflush(stdout);
    return 0;
}
