// 本题在 [POJ 2182] 提交

#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e5 + 10;

int n, a[N], c[N], ans[N];

int lowbit(int x) {
    return x & -x;
}

int query(int x) {
    int ret = 0;
    for (int i = x; i; i -= lowbit(i))
        ret += c[i];
    return ret;
}

void modify(int x, int delta) {
    for (int i = x; i <= n; i += lowbit(i))
        c[i] += delta;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 2; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) modify(i, 1);

    for (int i = n; i >= 1; i--) {
        int height = a[i] + 1;
        int l = 1, r = n;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (query(mid) >= height) r = mid;
            else l = mid + 1;
        }
        ans[i] = l;
        modify(l, -1);
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] << endl;

    fflush(stdout);
    return 0;
}
