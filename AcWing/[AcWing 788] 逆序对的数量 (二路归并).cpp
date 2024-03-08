#include <iostream>
using namespace std;
using i64 = long long;

const int N = 1e5 + 10;

int n, a[N], tmp[N];

i64 inversions(int l, int r) {
    if (l >= r) return 0LL;
    int mid = (l + r) >> 1;
    i64 ret = inversions(l, mid) + inversions(mid + 1, r);
    int lx = l, rx = mid + 1, idx = 0;
    while (lx <= mid && rx <= r)
        if (a[lx] <= a[rx]) {
            tmp[idx++] = a[lx++];
            ret += rx - mid - 1;
        } else
            tmp[idx++] = a[rx++];
    while (lx <= mid) tmp[idx++] = a[lx++], ret += r - mid;
    while (rx <= r) tmp[idx++] = a[rx++];
    for (int i = l, j = 0; i <= r; i++, j++) a[i] = tmp[j];
    return ret;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cout << inversions(1, n) << endl;
    return 0;
}
