// 参考题解：https://www.cnblogs.com/Proteinlzl/p/14824980.html

#include <iostream>

#define endl '\n'

using namespace std;

const int N = 2e5 + 5;

int n;
int a[N];

bool check(int x) {
    int wid = N;
    bool val = (a[1] >= x);

    for (int i = n; i <= n * 2 - 1; i++)
        if ((a[i] >= x) == (a[i + 1] >= x) && i - n < wid)
            wid = i - n, val = a[i] >= x;

    for (int i = n; i >= 1; i--)
        if ((a[i] >= x) == (a[i - 1] >= x) && n - i < wid)
            wid = n - i, val = a[i] >= x;

    return val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n * 2 - 1; i++) cin >> a[i];

    int l = 1, r = n * 2 - 1;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }

    cout << l << endl;
    return fflush(stdout), 0;
}
